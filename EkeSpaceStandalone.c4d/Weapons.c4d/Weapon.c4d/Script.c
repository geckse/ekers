#strict 2

func IsWeapon() { return true; }
func ActionString() { return ""; }

// weapon settings; array of values for each mode
// the mode names for the HUD; false for default
func Modes() { return [false]; }
func Automatic() { return [false]; }
func ShotDelay() { return [10]; }
func StopDelay() { return ShotDelay(); }
func AmmoID() { return [CA7A]; }
func AmmoUsage() { return [10]; }
func ShotSound() { return ["AR_Shoot"]; }
func ReloadSound() { return ["AR_Reload"]; }
func EmptySound() { return ["PT_Empty"]; }

func MuzzlePos() { return [4, 0]; }
func ShellPos() { return MuzzlePos(); }
func MuzzleFlashData() { return ["EkeMuzzleFlash2", 16, -1, 90, 85]; }

// ShotDelay is only a dummy effect
static const WP7A_ShotDelayEffect = "ShotDelay";
static const WP7A_AutoShootEffect = "AutoShoot";

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

func ChangeMode(int newMode, object clonk)
{
  if(IsShooting())
  {
    Stop();
  }

  modeIndex = newMode;

  mode = Modes()[modeIndex];
  ammo = modeAmmos[modeIndex];

  if(clonk)
  {
    clonk->ScrollHud(mode);
    clonk->SetAmmoBar(ammo);
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
  if(!ammo)
  {
    Sound(EmptySound()[modeIndex]);
    return FX_Execute_Kill;
  }

  Fire(clonk, dir, modeIndex);

  ammo -= AmmoUsage()[modeIndex];
  clonk->SetAmmoBar(ammo);
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
  if(ammo == 100) return false;

  var newAmmo = FindContents(AmmoID()[modeIndex], clonk);

  if(!newAmmo) return false;

  RemoveObject(newAmmo);

  Stop();

  ammo = 100;
  modeAmmos[modeIndex] = ammo;
  clonk->SetAmmoBar(ammo);

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

  if(!ammo)
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

func ControlThrow()
{
  Stop();
  return true;
}

func ControlShoot(object clonk, int axis)
{
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