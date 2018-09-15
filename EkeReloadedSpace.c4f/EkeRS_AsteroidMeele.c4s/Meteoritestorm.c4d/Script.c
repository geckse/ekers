/*-- Meteoritensturm --*/

#strict 2

protected func Initialize() {
	Wait();
}

private func Wait() {
	var iWait = GameCall("Meteoritestorm");
	if(!iWait)
		iWait = RandomX(1000, 10000);
	AddEffect("Waiting", this, 1, iWait, this);
}

protected func FxWaitingTimer(object pTarget, int iEffectNumber) {
	Schedule("AddEffect(\"Meteoritestorm\", this, 100, RandomX(10, 50), this);", 500, 0, this);
	return -1;
}

protected func FxMeteoritestormStart(object pTarget, int iEffectNumber, bool fTemp) {
	if(!fTemp){
			EffectVar(0, pTarget, iEffectNumber) = RandomX(10, 50);
   }
}

protected func FxMeteoritestormTimer(object pTarget, int iEffectNumber) {
	var i = EffectVar(0, pTarget, iEffectNumber)--;
	if(!i) {
		Wait();
		return -1;
	}

	var pObj = CreateObject(METO, Random(LandscapeWidth()), -100, NO_OWNER);
	pObj -> SetSpeed(RandomX(-60, 60), RandomX(10, 50));
}

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

public func IsChoosable() { return true; } // Regelwähler
