#strict 2
#appendto CLNK

func Initialize()
{
	AddEffect("CheckStuck2", this, 20, 1, this);
	DebugLog("HallO");
	return _inherited(...);
}

func FxCheckStuck2Timer(object pTarget, int iEffectNumber, int iEffectTime)
{
	if (!WildcardMatch(GetAction(pTarget), "*Walk")) return;

	var d = GetDir(pTarget)*2 - 1;
	if (!pTarget->GBackSolid(0, 4) && !pTarget->GBackSolid(d, 3) && pTarget->GBackSolid(d, 4))
	{
		SetPosition(GetX(pTarget), GetY(pTarget) - 1, pTarget);
		ObjectSetAction(pTarget, "KneelDown");
		pTarget->Schedule("SetXDir(0)", 1);
		if ((d == -1 && GetComDir(pTarget) != COMD_Left) || (d == 1 && GetComDir(pTarget) != COMD_Right)) SetComDir(COMD_Up, pTarget);
	}
}
