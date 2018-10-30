#strict 2
#appendto SF7A

local clonkCategory;

func Initialize()
{
    // add spawn protection
    clonkCategory = GetCategory(this);
    AddEffect("SpawnProtection",this,20,1,this);

    var ret = _inherited(...);

    SpawnClonk(this);

    return ret;
}


// spawn protection
func FxSpawnProtectionTimer(pTarget, iEffectNumber,iEffectTime) {
    EffectVar(3,pTarget,iEffectNumber)+=5;


    if(EffectVar(0,pTarget,iEffectNumber) <= 0)EffectVar(1,pTarget,iEffectNumber)=3;
    if(EffectVar(0,pTarget,iEffectNumber) >= 40)EffectVar(1,pTarget,iEffectNumber)=-3;


    if(Contained(pTarget))return(0);

    if(iEffectTime > 150) {
        SetClrModulation(RGB(255,255,255),pTarget);
        SetCategory(clonkCategory,pTarget);
        return(-1);
    }
    CreateParticle("PSpark",Cos(EffectVar(3,pTarget,iEffectNumber),10),Sin(EffectVar(3,pTarget,iEffectNumber),10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
    CreateParticle("PSpark",Cos(EffectVar(3,pTarget,iEffectNumber)-180,10),Sin(EffectVar(3,pTarget,iEffectNumber)-180,10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
    SetClrModulation(HSL(EffectVar(0,pTarget,iEffectNumber),255,128),pTarget);

    EffectVar(0,pTarget,iEffectNumber)+=EffectVar(1,pTarget,iEffectNumber);
    Extinguish(pTarget);
    SetCategory(C4D_Vehicle,pTarget);
}
func FxSpawnProtectionDamage(pTarget, iEffectNumber,foo,iCause) {
    return(0);
}