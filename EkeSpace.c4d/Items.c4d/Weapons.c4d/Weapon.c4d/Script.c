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
func ReloadTime() { return [false]; }
func AmmoID() { return CA7A; }
func AmmoUsage() { return [10]; }
func MaxAmmo() { return 1000; }
func ShotSound() { return ["AR_Shoot"]; }
func ReloadSound() { return "AR_Reload"; }
func EmptySound() { return ["PT_Empty"]; }

func MuzzlePos() { return [4, 0]; }
func ShellPos() { return MuzzlePos(); }
func MuzzleFlashData() { return ["EkeMuzzleFlash2", 16, -1, 90, 85]; }

// ShotDelay is only a dummy effect
static const WP7A_ShotDelayEffect = "ShotDelay";
static const WP7A_AutoShootEffect = "AutoShoot";
static const WP7A_ActiveEffect = "Active";
static const WP7A_ReloadEffect = "Reload";

// copy of current mode data for HUD and stuff
local ammo; // current mode's ammo in percent
local mode; // current mode's HUD name

local modeIndex; // current mode's index

local shootingAxis;

func ModeCount()
{
    return GetLength(Modes());
}

func Initialize()
{
    modeIndex = 0;
    mode = Modes()[0];
    Deactivated();
    ActivateWeapon();
}

func ControlSpecial2(object clonk)
{
    if(ModeCount() <= 1 || IsReloading())
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

func UpdateAmmoBar()
{
    var container = Contained();
    if(container && Contents(0, container) == this)
    {
        container->~SetAmmoBar(GetAmmoPercent());
    }
}

func SetAmmo(int amount)
{
    ammo = amount;

    UpdateAmmoBar();
    return true;
}

func SetAmmoPercent(int amount)
{
    return SetAmmo(amount * MaxAmmo() / 100);
}

func GetAmmo()
{
    return ammo;
}

func GetAmmoPercent()
{
    return 100 * ammo / MaxAmmo();
}

func AddAmmo(int amount)
{
    return SetAmmo(BoundBy(GetAmmo() + amount, 0, MaxAmmo()));
}

func ChangeMode(int newMode, object clonk)
{
    if(IsShooting())
    {
        Stop();
    }

    modeIndex = newMode;

    mode = Modes()[modeIndex];

    UpdateAmmoBar();
    if(clonk)
    {
        clonk->ScrollHud(mode);
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
        Empty();
        return FX_Execute_Kill;
    }

    Fire(clonk, dir, modeIndex);

    ammo -= AmmoUsage()[modeIndex];
    UpdateAmmoBar();
    if(!Automatic()[modeIndex])
    {
        var sound = ShotSound()[modeIndex];
        if(sound)
        {
            Sound(sound);
        }
    }

    if(ammo < AmmoUsage()[modeIndex])
    {
        Empty();
        return FX_Execute_Kill;
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

    // center bullet vertical
    y = 0;

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
    if(ammo >= MaxAmmo()) return false;

    var ammoIDs = AmmoID();
    if(GetType(ammoIDs) != C4V_Array)
    {
        ammoIDs = [ammoIDs];
    }

    var newAmmo;
    for(var ammoID in ammoIDs)
    {
        if(newAmmo = FindContents(ammoID, clonk))
        {
            break;
        }
    }

    if(!newAmmo) {
        DeactivateWeapon();
        return false;
    }

    RemoveObject(newAmmo);

    Stop();

    if(!ReloadTime()[modeIndex])
    {
        ammo = MaxAmmo();
        UpdateAmmoBar();
    }
    else
    {
        DeactivateWeapon();
        AddEffect(WP7A_ReloadEffect, this, 1, 1, this);
    }

    Sound(ReloadSound());
    return true;
}

func FxReloadTimer(object target, int effectNumber, int effectTime)
{
    var reloadTime = ReloadTime()[modeIndex];
    if(effectTime >= reloadTime)
    {
        return FX_Execute_Kill;
    }

    ammo = MaxAmmo() * effectTime / reloadTime;
    UpdateAmmoBar();
}

func FxReloadStop(object target, int effectNumber, int reason, bool temp)
{
    if(!temp)
    {
        ammo = MaxAmmo();
        UpdateAmmoBar();
    }
}

func IsReloading()
{
    return !!GetEffect(WP7A_ReloadEffect, this);
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
        && !GetEffect(WP7A_ShotDelayEffect, this)
        && !IsReloading();
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
        Empty();
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
        AddEffect(WP7A_ActiveEffect, this, 1, 0, this);
        var container = Contained();
        if(container) {
            var owner = GetOwner(container);
            if(owner != NO_OWNER) Sound("WP_Activate",1,this,100,owner+1);
        }
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

func FxActiveStart(object target, int effectNumber, int temp)
{
    if(temp == FX_Call_Normal)
    {
        Activated();
    }
}

func FxActiveTimer()
{
    if(GetAmmo() < AmmoUsage()[modeIndex]) {
        return FX_Execute_Kill;
    }

    // AddAmmo(-3);
    // PilotLight();
}

func FxActiveStop(object target, int effectNumber, int reason, bool temp)
{
    if(!temp)
    {
        Deactivated();
    }
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
    ControlShoot(ShootingAxis_Straight);
    return true;
}

func ControlCursorLeft() {
    ControlShoot(ShootingAxis_Straight);
    DebugLog("jau bruder");
    return true;
}

func ControlShoot(object clonk, int axis)
{
    if(!IsActive())
    {
        Empty();
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

func Empty()
{
    Sound(EmptySound()[modeIndex]);

    if(IsActive())
    {
        DeactivateWeapon();
    }
}

func Activated()
{
    var clonk = Contained();
    if(clonk && Contents(0, clonk) == this)
    {
        clonk->~WeaponActivated(this);
    }
}

func Deactivated()
{
    var clonk = Contained();
    if(clonk && Contents(0, clonk) == this)
    {
        clonk->~WeaponDeactivated(this);
    }
}