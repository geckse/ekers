/* Bombe */

#strict

local direction;

func Initialize()
{
  SetAction("Fly");
  if (Random(2)) SetDir(1);
  return(1);
}

func Flying()
{ 
  var rotSpeed = 50;
  
  if (InLiquid())
  {
    if (GetXDir() > 0)  SetXDir(GetXDir() - 1);
    if (GetXDir() < 0)  SetXDir(GetXDir() + 1);
    if (GetYDir() > 25) SetYDir(25);

    rotSpeed = 25;
    if (!Random(3)) Bubble();
  }
  var dir = GetR() / Abs(GetR());
  SetRDir(GetYDir() / rotSpeed * dir, 0, 1);
  return(1);
}

func Damage()
{
  if (GetDamage() < 1) return(1);
  return(Hit());
}

func Hit()
{
  Schedule("Explode(20)", 1);
  return(1);
}