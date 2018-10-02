/* Schrotflinte */

#strict

// Restmunition in Prozent
local ammo;

func ControlThrow(object clonk)
{ 
  if (!WildcardMatch(GetAction(clonk), "Shotgun*")) return(1);  

  if (GetAction() eq "Wait")   return(1);
  if (GetAction() eq "Reload") return(1);

  if (!ammo)
  {
    Sound("PT_Empty");
    return(1);
  }
  var dir = GetDir(clonk);

  for (var i = 0; i < 10; i++)
  {
    var bullet = CreateBullet(dir, clonk);
    if (i == 0) Sound("SG_Shoot", 0, bullet);
  }
  CreateMuzzleFlash(dir, clonk);

  SetAction("Wait");
 
  ammo -= 10;
  clonk -> SetAmmoBar(ammo);
  return(1);
}

func Activate(object clonk)
{ 
  if (ammo == 100) return(0);

  var cartridges = FindContents(CA7A, clonk);
  if (!cartridges) return(0);

  RemoveObject(cartridges);

  ammo = 100;
  clonk -> SetAmmoBar(ammo);

  Sound("SG_Reload");
  return(1);
}

func Reloading()
{
  if (!ammo) return;

  var clonk = Contained();
  if (clonk)
  {
    ScheduleCall(0, "CreateShell", 5, 0, GetDir(clonk));
    Sound("SG_Reload", 0, 0, 75);
  }    
}

func CreateBullet(dir, clonk)
{
  var x = 8 * dir - 4;
  var y = 0;

  var bullet = CreateObject(BU7A, x, y, NO_OWNER);
  bullet -> Launch(this(), dir, clonk);
  SetController(GetController(clonk), bullet);
  return(bullet);
}

func CreateMuzzleFlash(dir, clonk)
{
  var x = 34 * dir - 17;
  var y = -2 + dir;
  var a = 180 * dir - 90;

  CreateParticle("EkeMuzzleFlash3", x, y, Sin(a, 1000), -Cos(a, 1000), 100, 0, clonk);
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