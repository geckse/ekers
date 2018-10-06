/*-- Clean Up Effect --*/

#strict 2
#appendto ROCK
#appendto SP7A

// Effekt anhängen, der das Objekt nach einer Weile entfernt
func Initialize()
{
  if(arenaModeRule) AddEffect("CleanUp", this, 1, 2, this);
  return(_inherited(Par(0), Par(1)));
}

// Entfernt das Objekt nach einer Zeit (Durchschnittlich 250 Steine auf der Karte)
func FxCleanUpTimer(object pTarget, int iEffectNumber, int iEffectTime) {
  if(!Random(2)) EffectVar(0, pTarget, iEffectNumber)++;
  SetClrModulation(RGBa(255, 255, 255, EffectVar(0, pTarget, iEffectNumber)), pTarget);
  if(EffectVar(0, pTarget, iEffectNumber) >= 225)
  RemoveObject(pTarget);
}