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
  CastObjects(FG5B, 25, 100);
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
func ControlThrow(object clonk) {
  if (GetAction() ne "Activated") return(false);
  if (Contents (0, clonk) != this) return(false);

  if ((GetAction(clonk) eq "Walk") || (GetAction(clonk) eq "Jump") || (GetAction(clonk) eq "JetpackFly")) {
  var pClonk = clonk;
      
  // Wurfparameter
  var iX, iY, iR, iXDir, iYDir, iRDir, iDir;
  iDir = GetDir(pClonk)*2-1;
  iX = 10*iDir;
  iY = -6;
  iR = 90+60*iDir;
  iXDir = 4*iDir;
  iYDir = -2;
  iRDir = 4*iDir;

  // Werfen!
  Exit(this(), AbsX(iX+GetX(pClonk)), AbsY(iY+GetY(pClonk)), iR, iXDir, iYDir, iRDir);
  return (true);
  }
}