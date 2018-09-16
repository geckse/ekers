/*-- Stein --*/

#strict 2
#appendto ROCK

// Effekt anhängen, der den Stein nach einer Weile entfernt
func Initialize()	{
    AddEffect("CleanUp", this(), 1, 1, this(), ROCK);
	return(_inherited(Par(0), Par(1)));
}

// Entfernt das Objekt nach einer Zeit (Durchschnittlich 250 Steine auf der Karte)
func FxCleanUpTimer(object pTarget, int iEffectNumber, int iEffectTime) {
	if(!Random(2)) EffectVar(0, pTarget, iEffectNumber)++;
	SetClrModulation(RGBa(255, 255, 255, EffectVar(0, pTarget, iEffectNumber)), pTarget);
  if(EffectVar(0, pTarget, iEffectNumber) >= 225)
  	RemoveObject(pTarget);
}

// Bei zu viel Schaden zerlegt es den Stein (Durchschnittlich 200 Steine auf der Karte)
func Damage(int iChange, int iByPlayer) {
	if(GetDamage() < 60) return(0);
  RemoveObject();
}
