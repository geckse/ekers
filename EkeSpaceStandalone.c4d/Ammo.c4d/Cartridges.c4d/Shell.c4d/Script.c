/* Hülse */

#strict

local alpha;
local firstHit;

func Launch(int dir)
{
  // Drehung einleiten
  SetAction("Turn");
  SetDir(dir);

  // Flugrichtung setzen
  SetXDir((Random(5) + 5) * (-4 * dir + 2));
  SetYDir(Random(10) - 20);
  return(1);
}

func Hit()
{
  var m = GetMaterial(0, 1);

  if ((m == Material("Sky")) || (m == Material("Tunnel")))
  {
    SetXDir(-GetXDir());
    return(1);
  }
  SetAction("FadeOut");
  
  if (m == Material("Earth"))    return(0);
  if (m == Material("Sand"))     return(0);
  if (m == Material("FlySand"))  return(0);
  if (m == Material("Snow"))     return(0);
  if (m == Material("Coal"))     return(0);
  if (m == Material("Sulphur"))  return(0);
  if (m == Material("Ashes"))    return(0);
  if (m == Material("FlyAshes")) return(0);

  SetYDir(Min(GetActTime() + Random(5) - 15, 0));
  
  if(!GetActTime()) Sound("SH_Hit*");
  return(1);
}

func FadeOut()
{
  alpha++;
  if (alpha == 255)
  {
    RemoveObject();
    return(1);
  }
  SetClrModulation(RGBa(255, 255, 255, alpha));
  return(1);
}