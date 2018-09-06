/*-- Neues Script --*/

#strict

#appendto HG5B

func ControlThrow(object clonk) {
  if (GetAction() ne "Activated") return(false);
  if (Contents (0, clonk) != this) return(false);

  if ((GetAction(clonk) eq "Walk") || (GetAction(clonk) eq "Jump") || (GetAction(clonk) eq "JetpackFly")) {
  var pClonk = clonk;
  // Wurfparameter berechnen
  var iX, iY, iR, iXDir, iYDir, iRDir, iDir;
  iDir = GetDir(pClonk)*2-1;

  // Speerwurf
  iX = 10*iDir;
  iY = -6;
  iR = 90+60*iDir;
  iXDir = 5*iDir;
  iYDir = -2;
  iRDir = 4*iDir;

  // Werfen!
  Exit(this(), AbsX(iX+GetX(pClonk)), AbsY(iY+GetY(pClonk)), iR, iXDir, iYDir, iRDir);
  return (true);
  }
}