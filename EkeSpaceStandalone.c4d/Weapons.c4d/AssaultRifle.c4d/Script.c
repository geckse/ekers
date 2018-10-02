/* Sturmgewehr */

#strict

local ammo; // Restmunition in Prozent
local mode; // Feuermodus: Patronen oder Granaten

local qCartridges; // Menge der Patronen im Magazin
local qGrenades;   // Menge der Granaten im Magazin

local grenade; // gerade abgefeuerte Granate

func Initialize()
{
  mode = "Cartridges";
  return(1);
}
func ControlSpecial2(object clonk)
{
  if (mode == "Cartridges")
  {
    qCartridges = ammo;
    ammo = qGrenades;
    mode = "Grenades";
  }
  else
  {
    qGrenades = ammo;
    ammo = qCartridges; 
    mode = "Cartridges";
  }
  clonk -> ScrollHud(mode);
  clonk -> SetAmmoBar(ammo);
  return(1);
}

func Shooting()
{
  var clonk = Contained();
  var dir = GetDir(clonk);

  var b1 = !WildcardMatch(GetAction(clonk), "AssaultRifle*");
  var b2 = Contents(0, clonk) != this();
  var b3 = Contained(clonk);
  var b4 = mode == "Grenades";

  if (b1 || b2 || b3 || b4)
  {
    SetAction("Stop");
    return(1);
  }
  if (!ammo)
  {
    SetAction("Stop");
    Sound("PT_Empty");
    return(1);
  } 
  CreateBullet(dir, clonk);
  CreateMuzzleFlash(dir, clonk);
  CreateShell(dir);
 
  ammo--;
  clonk -> SetAmmoBar(ammo);
  return(1);
}

func Activate(object clonk)
{
  if (ammo == 100) return(0);  

  var newAmmo;
  var reloadSound;

  if (mode == "Cartridges")
  {
    newAmmo = FindContents(CA7A, clonk);
    reloadSound = "AR_Reload";
  }
  else
  {
    newAmmo = FindContents(GB7A, clonk);
    reloadSound = "GR_Reload";
  }
  if (!newAmmo) return(0);
  
  RemoveObject(newAmmo);
  SetAction("Stop");

  ammo = 100;
  clonk -> SetAmmoBar(ammo);

  Sound(reloadSound);
  return(1);
}

func CreateBullet(dir, clonk)
{
  var x = 8 * dir - 4;
  var y = 0;

  var bullet = CreateObject(BU7A, x, y, NO_OWNER);
  bullet -> Launch(this(), dir, clonk);
  SetController(GetController(clonk), bullet);
  return(1);
}

func CreateMuzzleFlash(dir, clonk)
{
  var x = 32 * dir - 16;
  var y = -2 + dir;
  var a = 180 * dir - 90;

  CreateParticle("EkeMuzzleFlash2", x, y, Sin(a, 1000), -Cos(a, 1000), 85, 0, clonk);
  return(1);
}

func CreateShell(dir)
{
  var x = 8 * dir - 4 - dir;
  var y = 0;
  
  var shell = CreateObject(SH7A, x, y);
  shell -> Launch(dir);
  return(1);
}

func CreateGrenade(dir, clonk)
{
  var x = 8 * dir - 4;
  var y = 1;
  
  var xDir = 20 * dir - 10;
  var yDir = -1;

  grenade = CreateContents(GR7A);
  Exit(grenade, x, y, 0, xDir, yDir);
  grenade -> Launch(clonk);
  SetController(GetController(clonk), grenade);
  return(1);
}

// Shoot
func ControlShoot()
{
  var clonk = Contained(this);
  if (!WildcardMatch(GetAction(clonk), "AssaultRifle*")) return(1);

  // zu schnelles Feuern unterbinden
  if (GetAction() eq "Stop") return(1);

  if (!ammo)
  {
    Sound("PT_Empty");
    return(1);
  }
  if (mode == "Cartridges")
  {
    if (GetAction() eq "Shoot")
    {
      SetAction("Stop");
    }
    else
    {
      SetAction("Shoot");
    }
  }
  else // Granate abfeuern
  {
    CreateGrenade(GetDir(clonk), clonk);
    SetAction("Stop");
    ammo -= 10;
    clonk -> SetAmmoBar(ammo);
    Sound("GR_Shoot");
  }
  return(1);
}