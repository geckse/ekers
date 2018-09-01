/* Flammenwerfer */

#strict

local ammo; // Restmunition in Prozent
local flipflop;
local calmCounter;
local yOld;

func ControlThrow(object clonk)
{
  if (!WildcardMatch(GetAction(clonk), "Icethrower*")) return(1);

  // zu schnelles Feuern unterbinden
  if (calmCounter < 0) return(1);

  if (!ammo)
  {
    Sound("FT_Empty");
    return(1);
  }
  if (GetAction() eq "Shoot")
  {
    SetAction("Stop");
    calmCounter = -10;
  }
  else
  {
    yOld = GetY();
    SetAction("Shoot");
  }
  return(1);
}

func Shooting()
{
  var clonk = Contained();
  var dir = GetDir(clonk);

  var b1 = !WildcardMatch(GetAction(clonk), "Icethrower*");
  var b2 = Contents(0, clonk) != this();
  var b3 = Contained(clonk);

  if (b1 || b2 || b3)
  {
    SetAction("Stop");
    return(1);
  }
  if (!ammo)
  {
    SetAction("Stop");
    Sound("FT_Empty");
    return(1);
  }
  CreateFire(clonk, dir);

  // Munition wird nur jedes zweite mal abgezogen
  flipflop = !flipflop;
  if (flipflop) ammo--;

  clonk->SetAmmoBar(ammo);
  return(1);
}

func Activate(object clonk)
{
  if (ammo == 100) return(0);

  var gas = FindContents(GS5B, clonk);
  if (!gas) return(0);

  RemoveObject(gas);
  SetAction("Stop");

  ammo = 100;
  clonk->SetAmmoBar(ammo);

  Sound("FT_Reload");
  return(1);
}

func PilotLight()
{
  if (calmCounter < 0) calmCounter++;

  if (!ammo) return(0);

  var clonk = Contained();
  var dir = GetDir(clonk);

  if (!WildcardMatch(GetAction(clonk), "Icethrower*")) return(0);

  var x = 20 * dir - 10 + Random(2);
  var y = RandomX(-3, -1);

  CreateParticle("PSpark", x, y, 0, -3, 20, RGBa(0, Random(2) * 100, 255, 120), clonk);
  return(1);
}

func CreateFire(object clonk, int dir)
{
  var x = 8 * dir - 4;
  var y = 0;

  var fire = CreateObject(IC5B, x, y, NO_OWNER);
  fire -> Launch(clonk, dir, GetY() - yOld);
  SetController(GetController(clonk), fire);

  yOld = GetY();
  return(1);
}