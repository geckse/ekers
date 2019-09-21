#strict 2

global func AddSpawnProtection(int time, bool showCountdown, bool disableControls, object target)
{
    return AddEffect("SpawnProtection", target || this, 20, 1, 0, 0, time, showCountdown, disableControls);
}

global func FxSpawnProtectionStart(object target, int effectNumber, int temp, int time, bool showCountdown, bool disableControls)
{
    if(!temp)
    {
        EffectVar(4, target, effectNumber) = GetCategory(target);
        EffectVar(5, target, effectNumber) = time;
        EffectVar(6, target, effectNumber) = showCountdown;
        EffectVar(7, target, effectNumber) = disableControls;

        if(disableControls)
        {
            var plr = GetOwner(target);
            for(var i = 0, crew; crew = GetCrew(plr, i); ++i)
            {
                crew->SetCrewEnabled(false);
            }

            SetPlrView(plr, target);
        }
    }
}

// spawn protection
global func FxSpawnProtectionTimer(target, effectNumber, effectTime)
{
    SetCategory(C4D_Vehicle, target);
    EffectVar(3,target,effectNumber)+=5;

    if(EffectVar(0,target,effectNumber) <= 0) EffectVar(1,target,effectNumber)=3;
    if(EffectVar(0,target,effectNumber) >= 40)EffectVar(1,target,effectNumber)=-3;


    if(Contained(target)) return;

    if(effectTime > EffectVar(5, target, effectNumber))
    {
        return FX_Execute_Kill;
    }

    if(EffectVar(6, target, effectNumber))
    {
        Message("<c %x>%d</c>", target, GetPlrColorDw(GetOwner(target)), (EffectVar(5, target, effectNumber) - effectTime) / 35 + 1);
    }

    target->CreateParticle("PSpark",Cos(EffectVar(3,target,effectNumber),10),Sin(EffectVar(3,target,effectNumber),10),0,0,30,HSL(EffectVar(0,target,effectNumber),255,128));
    target->CreateParticle("PSpark",Cos(EffectVar(3,target,effectNumber)-180,10),Sin(EffectVar(3,target,effectNumber)-180,10),0,0,30,HSL(EffectVar(0,target,effectNumber),255,128));
    SetClrModulation(HSL(EffectVar(0,target,effectNumber),255,128),target);

    EffectVar(0,target,effectNumber)+=EffectVar(1,target,effectNumber);
    Extinguish(target);
}

global func FxSpawnProtectionDamage(pTarget, iEffectNumber,foo,iCause)
{
    return 0;
}

global func FxSpawnProtectionStop(object target, int effectNumber, int reason, bool temp)
{
    if(!temp)
    {
        SetClrModulation(RGB(255,255,255), target);
        SetCategory(EffectVar(4, target, effectNumber), target);

        if(EffectVar(7, target, effectNumber))
        {
            target->SetCrewEnabled(true);

            var plr = GetOwner(target);
            for(var i = 0, crew; crew = GetCrew(plr, i); ++i)
            {
                crew->SetCrewEnabled(true);
            }

            SetCursor(plr, target);
        }

        if(EffectVar(6, target, effectNumber))
        {
            Message("", target);
        }
    }
}
