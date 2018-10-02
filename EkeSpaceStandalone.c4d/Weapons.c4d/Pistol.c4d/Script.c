/* Pistole */

#strict

local ammo;
local mode;

func Initialize()
{
  mode = "Pistol";
  return(1);
}

func ControlThrow(object clonk)
{ 
  if (!WildcardMatch(GetAction(clonk), "Pistol*")) return(1);  

  if (GetAction() eq "Wait") return(1);

  if (!ammo)
  {
    Sound("PT_Empty");
    return(1);
  }
  var dir = GetDir(clonk);

  CreateBullet(dir, clonk);
  CreateMuzzleFlash(dir, clonk);
  CreateShell(dir);

  SetAction("Wait");
 
  ammo -= 10;
  clonk -> SetAmmoBar(ammo);
  return(1);
}

func Activate(object clonk)
{ 
  if (ammo == 100) return(0);

  var magazine = FindContents(PM7A, clonk);
  if (!magazine) return(0);
  RemoveObject(magazine);

  ammo = 100;
  clonk -> SetAmmoBar(ammo);

  Sound("PT_Reload");
  return(1);
}

func CreateBullet(dir, clonk)
{
  var x = 8 * dir - 4;
  var y = -1;

  var bullet = CreateObject(BU7A, x, y, NO_OWNER);
  bullet -> Launch(this(), dir, clonk);
  SetController(GetController(clonk), bullet);
  return(1);
}

func CreateMuzzleFlash(dir, clonk)
{
  var x = 28 * dir - 14;
  var y = -4 + dir;
  var a = 180 * dir - 90;

  CreateParticle("EkeMuzzleFlash1", x, y, Sin(a, 1000), -Cos(a, 1000), 85, 0, clonk);
  return(1);
}

func CreateShell(dir)
{
  var x = 10 * dir - 5 - dir;
  var y = -1;
  
  var shell = CreateObject(SH7A, x, y);
  shell -> Launch(dir);
  return(1);
}