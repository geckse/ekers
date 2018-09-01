/* Airbike */

#strict

local ammo;        // Restmunition in Prozent
local mode;        // Cartridges || Rockets || Bombs || Contents

local qCartridges; // übrige Patronen
local qRockets;    // übrige Raketen
local qBombs;      // übrige Bomben
local qContents;   // übrige Inhaltsobjekte

func Initialize()
{
  mode = "Cartridges";  

  SetAction("Fly");
  SetComDir(COMD_Down());
  return(1);
}

func ControlLeft(object clonk)
{ 
  if (GetAction(clonk) ne "AirbikeFly") return(0);
  if (GetAction() ne "Fly") SetAction("Fly", clonk);
  
  SetDir(DIR_Left());
  SetDir(DIR_Left(), clonk);
  SetComDir(COMD_Left());
  return(1);
}

func ControlLeftDouble(object clonk)
{ 
  if (GetAction(clonk) ne "AirbikeFly") return(0);
  if (GetDir() != DIR_Left())           return(0);
  if (InLiquid())                       return(0);

  SetPhysical("Float", 800, 2);
  SetAction("Hyperfly", clonk);
  return(1);
}

func ControlRight(object clonk)
{ 
  if (GetAction(clonk) ne "AirbikeFly") return(0);
  if (GetAction() ne "Fly") SetAction("Fly", clonk);

  SetDir(DIR_Right());
  SetDir(DIR_Right(), clonk);
  SetComDir(COMD_Right());
  return(1);
}

func ControlRightDouble(object clonk)
{ 
  if (GetAction(clonk) ne "AirbikeFly") return(0);
  if (GetDir() != DIR_Right())          return(0);
  if (InLiquid())                       return(0);

  SetPhysical("Float", 800, 2);
  SetAction("Hyperfly", clonk);
  return(1);
}

func ControlUp(object clonk)
{ 
  if (GetAction(clonk) ne "AirbikeFly") return(0);
  SetComDir(COMD_Up());
  return(1);
}

func ControlDown(object clonk)
{ 
  if (GetAction(clonk) ne "AirbikeFly") return(0);

  // Absteigen
  if (Stuck() || GBackSolid(0, 11))
  {
    clonk -> SetAction("Walk");
    SetPhysical("Float", 0, 2);
    return(1);
  }
  SetComDir(COMD_Down());
  return(1);
}

func ControlThrow(object clonk)
{  
  if (GetAction(clonk) ne "AirbikeFly") return(0);
  if (GetAction() eq "Hyperfly")        return(1);

  // zu schnelles Feuern unterbinden
  if (WildcardMatch(GetAction(), "Wait*")) return(1);

  var dir = GetDir(clonk);

  if (mode == "Cartridges") ToggleShooting(clonk);
  if (mode == "Rockets")    LaunchRocket(dir, clonk);
  if (mode == "Bombs")      ReleaseObject(dir, clonk, 1);
  if (mode == "Contents")   ReleaseObject(dir, clonk, 0);

  return(1);
}

func ControlSpecial2(object clonk)
{
  if (GetAction(clonk) ne "AirbikeFly") return(1);
  if (GetAction() eq "Hyperfly")        return(1);

  var newAmmo;
  var newMode;

  if (mode == "Cartridges")
  {
    qCartridges = ammo;
    newAmmo = qRockets;
    newMode = "Rockets";
  }
  if (mode == "Rockets")
  {
    qRockets = ammo;
    newAmmo = qBombs;
    newMode = "Bombs";
  }
  if (mode == "Bombs")
  {
    qBombs = ammo; 
    newAmmo = qContents;
    newMode = "Contents";
  }
  if (mode == "Contents")
  {
    qContents = ammo;
    newAmmo = qCartridges;
    newMode = "Cartridges";
  }
  ammo = newAmmo;
  mode = newMode;

  clonk -> ScrollHud(mode);
  clonk -> SetAmmoBar(ammo);
  return(1);
}

func Activate(object clonk)
{
  if (ammo == 100) return(1);  

  var newAmmo;
  var reloadSound;

  if (mode == "Cartridges")
  {
    newAmmo = FindContents(CA5B, clonk);
    reloadSound = "AB_Reload1";
  }
  if (mode == "Rockets")
  {
    newAmmo = FindContents(RB5B, clonk);
    reloadSound = "AB_Reload2";
  }
  if (mode == "Bombs")
  {
    newAmmo = FindContents(BB5B, clonk);
    reloadSound = "AB_Reload2";
  }
  if (!newAmmo) return(1);
  
  RemoveObject(newAmmo);
  SetAction("WaitLong");

  ammo = 100;
  clonk -> SetAmmoBar(ammo);

  Sound(reloadSound);
  return(1);
}

func ControlRequest(object requester)
{
  // Airbike schon besetzt?
  if (!PilotLost()) return(0);

  requester -> SetAction("AirbikeFly", this());

  // wenn nicht über GPED gesteuert
  if (GetID(requester) == SF5B)
  {
    requester -> ScrollHud(mode);
    requester -> SetAmmoBar(ammo);

    SetComDir(COMD_None(), requester);
  }
  SetController(GetController(requester));
  SetActionTargets(requester);
  SetDir(GetDir(), requester);
  return(1);
}

func ToggleShooting(clonk)
{
  if (InLiquid()) return(1);
    
  if (!ammo)
  {
    SetAction("WaitShort");
    Sound("AB_Empty");
    return(1);
  }
  if (GetAction() eq "Shoot")
  {
    SetAction("WaitShort");
  }
  else
  {
    SetAction("Shoot", clonk);
  }
  return(1);
}

func LaunchRocket(dir, clonk)
{
  if (InLiquid()) return(1);

  if (!ammo)
  {
    SetAction("WaitShort");
    Sound("AB_Empty");
    return(1);
  }
  var x = 30 * dir - 15 - dir;
  var y = 2;
  
  var xDir = 20 * dir - 10;
  var yDir = 0;

  var rocket = CreateContents(RO5B);
  SetDir(dir, rocket);
  Exit(rocket, x, y, 0, xDir, yDir);
  SetController(GetController(clonk), rocket);

  SetAction("WaitLong");

  ammo -= 10;
  clonk -> SetAmmoBar(ammo);
  Sound("AB_Launch");
  return(1);
}

func ReleaseObject(dir, clonk, isBomb)
{
  if (!ammo)
  {
    SetAction("WaitShort");
    Sound("AB_Release");
    return(1);
  }
  var x = 0;
  var y = 17; 
  var r = 0;
  
  var xDir = GetXDir() / 10;
  var yDir = GetYDir() / 10;  

  var object;

  if (isBomb)
  {
    object = CreateContents(BO5B);

    r = 180 * dir - 90;

    ammo -= 10; // Ausgleich, denn Contents macht +10
    clonk -> SetAmmoBar(ammo);
  }
  else
  {
    object = Contents();

    if (GetID(object) == TRP1)
    {
      if(GetAction() eq "Dive")
      {
        x = 66 * dir - 33;
        y = 3;
        
        xDir = 2 * dir -1;
        yDir = 0;

        object -> Launch(this());
      }
    }
  }
  Exit(object, x, y, r, xDir, yDir);
  SetController(GetController(clonk), object);

  SetAction("WaitShort");
  Sound("AB_Release");
  return(1);
}

func Flying()
{
  PilotLost();

  var value = GetPhysical("Float");

  if (value < 200) value = 200;
  if (value > 200) value -= 50;

  SetPhysical("Float", value, 2);
  return(1);
}

func Hyperflying()
{
  PilotLost();  

  var dir = GetDir();

  var x1 = -58 * dir + 29;
  var x2 = -48 * dir + 24;

  var y = -4 + dir;
  var a = 180 * dir - 90;

  var xDir = Sin(a, 1000);
  var yDir = -Cos(a, 1000);
 
  var s1 = 150;
  var s2 = 75;
 
  var c1 = RGBa(255, RandomX(50, 100), 100, 150);
  var c2 = RGBa(255, RandomX(50, 100), 0, 100);
  
  CreateParticle("EkeAfterburner2", x1, y, xDir, yDir, s1, c1, this()); // außen
  CreateParticle("EkeAfterburner2", x2, y, xDir, yDir, s2, c2, this()); // innen
  return(1);
}

func Shooting()
{
  if (PilotLost()) return(1);

  if (mode != "Cartridges")
  {
    SetAction("WaitShort");
    return(1);
  }
  if (!ammo)
  {
    SetAction("WaitShort");
    Sound("AB_Empty");
    return(1);
  }
  var clonk = GetActionTarget();
  var dir = GetDir();

  CreateBullet(dir, clonk);
  CreateMuzzleFlash(dir);
  CreateShell(dir);
  
  ammo--;
  clonk -> SetAmmoBar(ammo);
  return(1);
}

func CreateBullet(dir, clonk)
{
  var x = 30 * dir - 15;
  var y = 1;

  var bullet = CreateObject(BU5B, x, y, NO_OWNER);
  bullet -> Launch(this(), dir, this());
  SetController(GetController(clonk), bullet);
  return(1);
}

func CreateMuzzleFlash(dir)
{
  var x = 44 * dir - 22;
  var y = -2 + dir;
  var a = 180 * dir - 90;

  CreateParticle("EkeMuzzleFlash3", x, y, Sin(a, 1000), -Cos(a, 1000), 85, 0, this());
  return(1);
}

func CreateShell(dir)
{
  var x = 16 * dir - 8 - dir;
  var y = 3;
  
  var shell = CreateObject(SH5B, x, y);
  shell -> Launch(dir);
  return(1);
}

func Diving()
{
  PilotLost();

  SetPhysical("Float", 100, 2);
  return(1);
}

func PilotLost()
{
  var clonk = GetActionTarget();
  if (GetAction(clonk) eq "AirbikeFly") return(0);

  if (GetAction() ne "Fly") SetAction("Fly");
  SetComDir(COMD_Down());
  return(1);
}

func Collection2()
{
  if (mode == "Contents")
  {
    ammo += 10;
    if (!PilotLost())
    {
      var clonk = GetActionTarget();
      clonk -> SetAmmoBar(ammo);
    }
  }
  else
  {
    qContents += 10;
  }
}

func Ejection()
{
  if (mode == "Contents")
  {
    ammo -= 10;
    if (!PilotLost())
    {
      var clonk = GetActionTarget();
      clonk -> SetAmmoBar(ammo);
    }
  }
  else
  {
    qContents -= 10;
  }
}

func Entrance()
{
  var clonk = GetActionTarget();
  if (GetAction(clonk) ne "AirbikeFly") return(0);

  // Piloten absetzten
  clonk -> SetAction("Walk");
  SetPhysical("Float", 0, 2);
  return(1);
}

func Hit()
{
  if (Abs(GetXDir()) < 70) return;
  Explode(50);
  return(1);  
}

func Damage()
{
  if (GetDamage() < 30) return(1);
  Schedule("Explode(50)", 1);
  return(1);
}

func GPEDControlSelection(gped, query)
{
  if (query)
  {
    if (Hostile(GetOwner(), GetOwner(gped), 1)) return(0);
    if (!PilotLost())                           return(0);

    // kann vom GPED gefunden werden
    return(1);
  }
  ControlRequest(gped);
  Sound("AB_Select");
  return(1); 
}