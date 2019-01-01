/* Lenkrakete */

local target;
local targetFoundTime;
local random;
local aggro;

#strict 2

func Launch(rocketLauncher)
{
    SetAction("Fly");
    Sound("JP_Launch");
    return 1;
}

func Flying()
{
    aggro = 1;
    
    if((GetActTime() > 500) || (InLiquid()))
    {
        SetAction("Tumble");
        return 1;
    }

    var offset = 10;
    if(random)
    {
        SetRDir(BoundBy(RandomX(-10, 10) + GetRDir(), -25, 25));
    }
    else
    {
        if(GetActTime() < 3) offset += 20;

        if(targetFoundTime && FrameCounter() - targetFoundTime > 30)
        {
            target = 0;
        }
        else if(!target)
        {
            if(target = FindTargets(this, 200, 25, GetR())[0])
            {
                targetFoundTime = FrameCounter();
            }
        }

        if(target)
        {
            var iDAngle = Angle(GetX(),GetY(),GetX(target),GetY(target));
            var iAngle = GetR();

            var iDiff = Normalize(iDAngle - iAngle,-180);
            var iTurn = Min(Abs(iDiff), 4);

            SetR(iAngle+iTurn*((iDiff > 0)*2-1));
        }
        
        if(aggro) if(EkeFindVictim(-5, -10, 10, 20, this)) return BlowUp();
    }

    SetXDir(Sin(GetR(), 50));
    SetYDir(-Cos(GetR(), 50));

    CreateSmokeFX(offset);
    CreateFireFX(offset - 5);
    return 1;
}

func CreateSmokeFX(offset)
{
    var n = "EkeSmoke";
    var a = Random(5) + 5;
    var l = 10;

    var x = -Sin(GetR(), offset);
    var y = +Cos(GetR(), offset);

    var sMin = 40;
    var sMax = 80;

    var cMin = RGBa(255, 255, 255, 100);
    var cMax = RGBa(255, 255, 255, 200);

    CastParticles(n, a, l, x, y, sMin, sMax, cMin, cMax);
    return 1;
}

func CreateFireFX(offset)
{
    var n = "Fire2";
    var a = Random(10) + 10;
    var l = 20;

    var x = -Sin(GetR(), offset);
    var y = +Cos(GetR(), offset);

    var sMin = 25;
    var sMax = 75;

    var cMin = RGBa(255, 200, 000, 200);
    var cMax = RGBa(255, 255, 150, 150);

    CastParticles(n, a, l, x, y, sMin, sMax, cMin, cMax);
    return 1;
}

func Tumbling()
{
    if(InLiquid())
    {
        if(GetXDir() > 0)  SetXDir(GetXDir() - 1);
        if(GetXDir() < 0)  SetXDir(GetXDir() + 1);
        if(GetYDir() > 25) SetYDir(25);

        if(!Random(3)) Bubble();
    }
    SetR(Angle(0, 0, GetXDir(), GetYDir()));
    return 1;
}

func BlowUp()
{
    if(GetAction() != "Idle")
    {
        // Sprengsatz zünden
        Schedule("Explode(30)", 1);
    }
    else
    {
        // Fehlzündung
        Launch();
        random = true;
    }
    return 1;
}

func Damage()
{
    if(GetAction() == "Idle")
    {
        if(GetDamage() < 1) return 1;

        return BlowUp();
    }
}

func Hit()
{
    return BlowUp();
}

func RejectEntrance()
{
    if(GetAction() != "Idle") return true;
}