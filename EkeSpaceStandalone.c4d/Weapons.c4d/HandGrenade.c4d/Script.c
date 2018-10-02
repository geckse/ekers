/* Handgranate */

#strict

func Activate(object clonk)
{
  // Zeitzünder kann nicht verzögert werden
  if (GetAction() eq "Activated") return(1);

  SetAction("Activated");
  SetPicture(40, 0, 35, 35);
  Sound("HG_PullPin");
  return(1);
}

func BlowUp()
{
  CastObjects(FG7A, 25, 100);
  Explode(30);
  return(1);
}     

func Damage()
{
  if (GetDamage() < 1) return(1);
  ScheduleCall(0, "BlowUp", 1);
  return(1);
}

func Hit()
{
  Sound("MetalHit*");
  return(1);
}

func FX()
{
  if (Contained()) return(0);
  if (InLiquid())  return(0);

  if (Abs(GetXDir()) + Abs(GetYDir()) > 10)
  {
    CreateParticle("PSpark", RandomX(-3, 3), RandomX(-8, -2), 0, 0, 150, RGBa(255, Random(2) * 100, 0, 120));
    CreateParticle("PSpark", RandomX(-3, 3), RandomX(-8, -2), 0, 0, 125, RGBa(255, Random(2) * 100, 0, 120));
    CreateParticle("PSpark", RandomX(-3, 3), RandomX(-8, -2), 0, 0, 100, RGBa(255, Random(2) * 100, 0, 120));
  }
  else
  {
    CreateParticle("PSpark", Random(2), RandomX(-6, -4), GetWind() / 10, -5, 40, RGBa(255, Random(2) * 100, 0, 120));
  }
  return(1);
}