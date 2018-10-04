#strict 2

func IsWeapon() { return true; }
func ActionString() { return ""; }

func NeedsActivation() { return true; }

// weapon settings; array of values for each mode
// the mode names for the HUD; false for default
func Modes() { return [false]; }
func Automatic() { return [false]; }
func ShotDelay() { return [10]; }
func StopDelay() { return ShotDelay(); }
func AmmoID() { return [CA7A]; }
func AmmoUsage() { return [10]; }
func MaxAmmo() { return [1000]; }
func ShotSound() { return ["AR_Shoot"]; }
func ReloadSound() { return ["AR_Reload"]; }
func EmptySound() { return ["PT_Empty"]; }

func MuzzlePos() { return [4, 0]; }
func ShellPos() { return MuzzlePos(); }
func MuzzleFlashData() { return ["EkeMuzzleFlash2", 16, -1, 90, 85]; }

// ShotDelay is only a dummy effect
static const WP7A_ShotDelayEffect = "ShotDelay";
static const WP7A_AutoShootEffect = "AutoShoot";
static const WP7A_ActiveEffect = "Active";

static const WP7A_All = -1;

// copy of current mode data for HUD and stuff
local ammo; // current mode's ammo in percent
local mode; // current mode's HUD name

local modeIndex; // current mode's index
local modeAmmos; // current ammo of all modes

local shootingAxis;

func ModeCount()
{
  return GetLength(Modes());
}

func Initialize()
{
  modeIndex = 0;
  modeAmmos = CreateArray(ModeCount());
  mode = Modes()[0];
}

func ControlSpecial2(object clonk)
{
  if(ModeCount() <= 1)
  {
    return false;
  }

  var newMode = modeIndex + 1;

  if(newMode >= ModeCount())
  {
    newMode = 0;
  }

  ChangeMode(newMode, clonk);
  return true;
}

func UpdateCurrentAmmo()
{
  ammo = modeAmmos[modeIndex];
  var container = Contained();
  if(container && Contents(0, container) == this)
  {
    container->~SetAmmoBar(GetAmmoPercent());
  }
}

func AffectedMode(int modePlusOne)
{
  // wrong input
  if(modePlusOne > ModeCount() || modePlusOne < 0) return ModeCount();

  if(modePlusOne == 0) return modeIndex;
  return modePlusOne - 1;
}

// Set/Get the current ammo amount for the current or a specific mode
// If modePlusOne is omitted or zero, the current mode's ammo is returned
// otherwise modePlusOne specifies the desired index increased by one

// For SetAmmo the constant WP7A_All can be used to set the ammo for all available modes

func SetAmmo(int amount, int modePlusOne)
{
  if(modePlusOne == WP7A_All)
  {
    for(var i = 0; i < ModeCount(); ++i)
    {
      modeAmmos[i] = amount;
    }
    UpdateCurrentAmmo();
    return true;
  }

  var affectedMode = AffectedMode(modePlusOne);
  if(affectedMode >= ModeCount())
  {
    return false;
  }

  modeAmmos[affectedMode] = amount;

  if(affectedMode == modeIndex)
  {
    UpdateCurrentAmmo();
  }

  return true;
}

func SetAmmoPercent(int amount, int modePlusOne)
{
  if(modePlusOne == WP7A_All)
  {
    for(var i = 0; i < ModeCount(); ++i)
    {
      modeAmmos[i] = amount * MaxAmmo()[i] / 100;
    }
    UpdateCurrentAmmo();
    return true;
  }

  var affectedMode = AffectedMode(modePlusOne);
  if(affectedMode >= ModeCount())
  {
    return false;
  }

  modeAmmos[affectedMode] = amount * MaxAmmo()[affectedMode] / 100;

  if(affectedMode == modeIndex)
  {
    UpdateCurrentAmmo();
  }

  return true;
}

func GetAmmo(int modePlusOne)
{
  var affectedMode = AffectedMode(modePlusOne);
  if(affectedMode >= ModeCount())
  {
    return -1;
  }

  return modeAmmos[affectedMode];
}

func GetAmmoPercent(int modePlusOne)
{
  var affectedMode = AffectedMode(modePlusOne);
  if(affectedMode >= ModeCount())
  {
    return -1;
  }

  return 100 * modeAmmos[affectedMode] / MaxAmmo()[affectedMode];
}

func AddAmmo(int amount, int modePlusOne)
{
  var affectedMode = AffectedMode(modePlusOne);
  if(affectedMode >= ModeCount())
  {
    return false;
  }

  return SetAmmo(BoundBy(GetAmmo(modePlusOne) + amount, 0, MaxAmmo()[affectedMode]), modePlusOne);
}

func ChangeMode(int newMode, object clonk)
{
  if(IsShooting())
  {
    Stop();
  }

  // for backward compatibility reasons
  modeAmmos[modeIndex] = ammo;

  modeIndex = newMode;

  mode = Modes()[modeIndex];
  ammo = modeAmmos[modeIndex];

  if(clonk)
  {
    clonk->ScrollHud(mode);
    clonk->SetAmmoBar(GetAmmoPercent());
  }
}

func Shooting()
{
  var clonk = Contained();
  var dir = GetDir(clonk);

  if(!ReadyToShoot(clonk))
  {
    return FX_Execute_Kill;
  }
  if(ammo < AmmoUsage()[modeIndex])
  {
    Sound(EmptySound()[modeIndex]);
    return FX_Execute_Kill;
  }

  Fire(clonk, dir, modeIndex);

  ammo -= AmmoUsage()[modeIndex];
  clonk->SetAmmoBar(GetAmmoPercent());
  modeAmmos[modeIndex] = ammo;
  if(!Automatic()[modeIndex])
  {
    var sound = ShotSound()[modeIndex];
    if(sound)
    {
      Sound(sound);
    }
  }
  return true;
}

func Fire(object clonk, int dir, int mode)
{
  CreateBullet(dir, clonk);
  CreateMuzzleFlash(dir, clonk);
  CreateShell(dir);
}

func CreateBullet(dir, clonk)
{
  var pos = MuzzlePos();
  var x = (dir * 2 - 1) * pos[0] - dir * pos[2];
  var y = pos[1];

  var bullet = CreateObject(BU7A, x, y, NO_OWNER);
  bullet->Launch(this, dir, clonk);
  SetController(GetController(clonk), bullet);
  return bullet;
}

func CreateMuzzleFlash(dir, clonk)
{
  var data = MuzzleFlashData();
  var signDir = dir * 2 - 1;
  var x = signDir * data[1];
  var y = data[2] + dir;
  var a = signDir * data[3];

  CreateParticle(data[0], x, y, Sin(a, 1000), -Cos(a, 1000), data[4], 0, clonk);
  return true;
}

func CreateShell(dir)
{
  var pos = ShellPos();
  var x = (dir * 2 - 1) * pos[0] - dir * pos[2];
  var y = pos[1];

  var shell = CreateObject(SH7A, x, y);
  shell->Launch(dir);
  return true;
}

func Activate(object clonk)
{
  if(ammo >= MaxAmmo()[modeIndex]) return false;

  var newAmmo = FindContents(AmmoID()[modeIndex], clonk);

  if(!newAmmo) return false;

  RemoveObject(newAmmo);

  Stop();

  ammo = MaxAmmo()[modeIndex];
  modeAmmos[modeIndex] = ammo;
  clonk->SetAmmoBar(GetAmmoPercent());

  Sound(ReloadSound()[modeIndex]);
  return true;
}

func IsShooting()
{
  return !!GetEffect(WP7A_AutoShootEffect, this);
}

func ToggleShooting()
{
  if(IsShooting())
  {
    return Stop();
  }
  else
  {
    return Shoot();
  }
}

func ReadyToShoot(object clonk)
{
  return WildcardMatch(GetAction(clonk), Format("%s*", ActionString()))
    && Contents(0, clonk) == this
    && !Contained(clonk)
    && !GetEffect(WP7A_ShotDelayEffect, this);
}

func Shoot()
{
  var clonk = Contained(this);
  if(!ReadyToShoot(clonk) || GetEffect(WP7A_AutoShootEffect, this))
  {
    return true;
  }

  if(ammo < AmmoUsage()[modeIndex])
  {
    Sound(EmptySound()[modeIndex]);
    return true;
  }

  if(Shooting() != FX_Execute_Kill)
  {
    var effect = [WP7A_ShotDelayEffect, WP7A_AutoShootEffect][Automatic()[modeIndex]];
    AddEffect(effect, this, 1, ShotDelay()[modeIndex], this);
  }
  return true;
}

func Stop()
{
  if(IsShooting())
  {
    RemoveEffect(WP7A_AutoShootEffect, this);
    AddEffect(WP7A_ShotDelayEffect, this, 1, StopDelay()[modeIndex], this);
    return true;
  }
}

func FxAutoShootStart(object target, int effectNumber, int temp)
{
  if(!temp)
  {
    Sound(ShotSound()[modeIndex], false, this, 100, 0, +1);
  }
}

func FxAutoShootTimer(object target, int effectNumber)
{
  return Shooting();
}

func FxAutoShootStop(object target, int effectNumber, int reason, bool temp)
{
  if(!temp)
  {
    Sound(ShotSound()[modeIndex], false, this, 100, 0, -1);
  }
}

func GetShootingAxis()
{
  return shootingAxis;
}

func IsActive()
{
  return !NeedsActivation() || GetEffect(WP7A_ActiveEffect, this);
}

func ActivateWeapon()
{
  if(!IsActive())
  {
    AddEffect(WP7A_ActiveEffect, this, 1, 2, this);
    Sound("WP_Activate");
  }
}

func DeactivateWeapon()
{
  Stop();

  if(NeedsActivation() && IsActive())
  {
    RemoveEffect(WP7A_ActiveEffect, this);
  }
}

func PilotLight()
{
  var clonk = Contained();
  var dir = GetDir(clonk);

  if (!ReadyToShoot(clonk)) return;

  var pos = MuzzlePos();

  var x = pos[0] * (dir * 2 - 1) + Random(2);
  var y = pos[1];

  CreateParticle("PSpark", x, y, 0, -1, 20, GetColorDw(clonk), clonk);
  CreateParticle("PSpark", x, y, 0, 0, 20, RGBa(255,255,255,120), clonk);
}


func FxActiveTimer()
{
  var container = Contained();
  if(!container || Contents(0, container) != this)
  {
    return FX_Execute_Kill;
  }

  AddAmmo(-3);
  PilotLight();
}

func ToggleActivation()
{
  if(IsActive())
  {
    DeactivateWeapon();
  }
  else
  {
    ActivateWeapon();
  }
}

func ControlThrow()
{
  if(NeedsActivation())
  {
    ToggleActivation();
  }
  return true;
}

func ControlShoot(object clonk, int axis)
{
  if(!IsActive())
  {
    return false;
  }

  if(shootingAxis == axis && IsShooting())
  {
    Stop();
  }
  else
  {
    shootingAxis = axis;
    Shoot();
  }
  return true;
}
