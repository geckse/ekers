/* Raketenwerfer */

#strict

func IsWeapon() { return true; }
func ActionString() { return "RocketLauncher"; }

local ammo;    // Restmunition in Prozent
local missile; // Lenkrakete im Flug
local guiding; // SFT ist am Lenken

func ControlLeft(object clonk)
{
  if (!guiding) return(0);

  SetPlrView(GetOwner(clonk), missile);
  LocalN("command", missile) = "Left";
  return(1);
}

func ControlLeftDouble(object clonk)
{
  return(ControlLeft(clonk));
}

func ControlRight(object clonk)
{
  if (!guiding) return(0);

  SetPlrView(GetOwner(clonk), missile);
  LocalN("command", missile) = "Right";
  return(1);
}

func ControlRightDouble(object clonk)
{
  return(ControlRight(clonk));
}

func ControlUp(object clonk)
{
  return(ControlDown(clonk));
}

func ControlDown(object clonk)
{
  if (!guiding) return(0);

  SetPlrView(GetOwner(clonk), missile);
  LocalN("command", missile) = "Straight";
  return(1);
}

func ControlThrow(object clonk)
{
  if (!WildcardMatch(GetAction(clonk), "RocketLauncher*")) return(1);

  if (guiding)
  {
    SetPlrView(GetOwner(clonk), missile);
    LocalN("command", missile) = "Explode";
    clonk -> SetAmmoBar(0);
    return(1);
  }
  if (GetAction() eq "Wait")   return(1);
  if (GetAction() eq "Reload") return(1);

  if (!ammo)
  {
    Sound("PT_Empty");
    return(1);
  }
  var dir = GetDir(clonk);

  var x = 20 * dir - 10;
  var y = 2;
  var r = 180 * dir - 90;

  missile = Contents();

  SetDir(dir, missile);
  Exit(missile, x, y, r);
  missile -> Launch(this());
  SetController(GetController(clonk), missile);

  SetAction("Wait");

  ammo -= 100;
  clonk -> SetAmmoBar(ammo);
  Sound("RL_Shoot");
  return(1);
}

func ControlDig(object clonk)
{
  if (missile)
  {
    if (guiding)
    {
      guiding = 0;
      clonk -> SetAmmoBar(0);
    }
    else
    {
      guiding = 1;

      SetComDir(COMD_Stop(), clonk);
      SetPlrView(GetOwner(clonk), missile);
      Sound("AB_Select");
    }
  }
  return(1);
}

func ControlDigSingle()
{
  if (!missile) return(0);
  return(1);
}

func Reloading()
{
  var clonk = Contained();
  if (clonk)
  {
    // SFT darf sich beim Laden nicht anders beschäftigen
    if (!WildcardMatch(GetAction(clonk), "RocketLauncher*")) return;

    ammo += 2;
    clonk -> SetAmmoBar(ammo);
    if (ammo == 100) SetAction("Wait");
  }
  return(1);
}

func Activate(object clonk)
{
  if (ammo > 0) return(0);
  if (guiding)  return(0);

  var cMissile = FindContents(MS7A, clonk);
  if (!cMissile) return(0);
  Enter(this(), cMissile);

  SetAction("Reload");
  Sound("RL_Reload");
  return(1);
}

func GetAmmoPercent()
{
	return ammo;
}