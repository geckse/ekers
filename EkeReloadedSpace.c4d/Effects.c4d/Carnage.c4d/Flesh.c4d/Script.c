/*--- Clonkarm ---*/

// script v1.0 by minwipf
#strict 2

protected func Initialize()
{
  AddEffect("Bleed", this, 101, 1,, CFLS);
  Schedule("FadeCorp(this())",RandomX(80,170),1,this);
  return 1;
}

protected func Hit()
{
  Sound("WoodHit*");
   CastObjects(BLOP,(GetXDir()+GetYDir())/6,(GetXDir()+GetYDir())/2);
  return 1;
}
public func CorpPart(){ return(true); }

protected func FxBleedTimer(object pTarget, int iNr, int iTime)
{
  if (iTime > 50) return -1;
  if(!Random(2)){
   var val = 1;
   CastObjects(BLOP,(GetXDir()+GetYDir())/6,2);
  }
  return 1;
}