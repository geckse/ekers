/* Kugel */

#strict 2

local xOld;
local yOld;

local shooter;
local direction;
local flightTime;

local yVariation;
local mAmount;
local mLevel;
local holeSize;
local punch;
local shootingAxis;

func Launch(object weapon, int dir, clonk)
{
    if (GetID(weapon) == PT7A) Pistol();
    if (GetID(weapon) == UZ7A) Uzi();
    if (GetID(weapon) == AR7A) AssaultRifle();
    if (GetID(weapon) == AB7A) Airbike();
    if (GetID(weapon) == SG7A) Shotgun();

    shootingAxis = weapon->~GetShootingAxis();

    xOld = GetX();
    yOld = GetY() + shootingAxis * 4;

    shooter = clonk;
    direction = 2 * dir - 1;


    SetXDir(direction * 400);
    SetAction("Fly");
    return(1);
}

func Pistol()
{
    yVariation = 0;
    mAmount = 20;
    mLevel = 40;
    holeSize = 5;
    punch = 8;

    Sound("PT_Shoot*");
    return(1);
}

func Uzi()
{
    yVariation = 100;
    mAmount = 20;
    mLevel = 40;
    holeSize = 5;
    punch = 4;

    return(1);
}

func AssaultRifle()
{
    yVariation = 25;
    mAmount = 50;
    mLevel = 50;
    holeSize = 8;
    punch = 6;

    return(1);
}

func Airbike()
{
    yVariation = 25;
    mAmount = 50;
    mLevel = 50;
    holeSize = 8;
    punch = 8;

    return(1);
}

func Shotgun()
{
    yVariation = 50;
    mAmount = 10;
    mLevel = 30;
    holeSize = 3;
    punch = 3;

    return(1);
}

func HitObject()
{
    flightTime = BoundBy(GetActTime(), 1, 6);
    if (flightTime > 5) RemoveObject();

    // y-Abweichung der Kugel einbringen
    SetYDir(RandomX(-yVariation, yVariation) + shootingAxis * 180);

    var notFree = false;

    var x = xOld - GetX();
    var y = yOld - GetY();

    if(!PathFree2(xOld, yOld, GetX(), GetY()))
    {
        SetPosition(xOld, yOld);
        direction = 0;
        notFree = true;
    }

    xOld = GetX();
    yOld = GetY();


    var a1 = Find_OnLine(x, y, 0, 0);
    var a2 = Find_NoContainer();
    var a3 = Find_Exclude(shooter);
    var a4 = Sort_Distance(x, y);


    for (var victim in FindObjects(a1, a2, a3, a4))
    {
        if (HitCreature(victim)) return(1);
        if (HitBalloon(victim))  return(1);
        if (HitTin(victim))      return(1);
    }

    if(notFree)
    {
        Hit(0, 0, true);
    }
    return(0);
}

func Hit(int oldXDir, int oldYDir, bool noObject)
{
    if (!noObject && HitObject()) return;

    if (!GBackSolid(direction))
    {
        return(1);
    }
    var m = GetMaterial(direction);
    if (GetMaterialVal("DigFree", "Material", m))
    {
        HitSoft(MaterialName(m));
        return(1);
    }
    HitHard();
    return(1);
}

func HitSoft(material)
{
    CastPXS(material, mAmount, mLevel);
    DigFree(GetX(), GetY(), holeSize);

    Sound("BU_SoftHit*");
    RemoveObject();
    return(1);
}

func HitHard()
{
    for (var i = 0; i < 5; i++)
    {
        var xDir = Random(25) * -direction;
        var yDir = RandomX(-25, 25);

        CreateParticle("PxSpark", 0, 0, xDir, yDir, 40, RGBa(255, 255, 0, 150));

        if (punch < 5) break; // Shotgun
    }
    Sound("BU_HardHit*");
    RemoveObject();
    return(1);
}

func HitCreature(victim)
{
    var p1 = GetController();
    var p2 = GetController(victim);

    if (ObjectCount(NF7A) && !Hostile(p1, p2, 1)) return(0); // kein Friendly Fire
    if (!(GetOCF(victim) & OCF_Alive))            return(0); // Opfer muß noch leben
    if (GetID(victim) == ZAP1)                    return(0); // Zaps nicht beachten

    // Tiere werden härter getroffen als Clonks
    var booster = 1;
    if (!(GetOCF(victim) & OCF_CrewMember)) booster++;

    // dem Opfer Energie abziehen
    DoEnergy(-punch * booster, victim);

    // Schockwellengeschosse aktiviert?
    if (ObjectCount(SW7A))
    {
        // Piloten nicht vom Airbike reißen
        if (GetAction(victim) != "AirbikeFly")
        {
            // nicht bei schweren (großen) Lebewesen
            if (GetMass(victim) < 500)
            {
                var iYDir = -1 * booster;
                var procedure = GetProcedure(victim);
                
                // Schussachse nicht berücksichtigen wenn Clonk steht oder klettert
                if(procedure != "WALK" && procedure != "HANGLE" && procedure != "SCALE" && procedure != "KNEEL") {
                    if(shootingAxis) iYDir = shootingAxis * 2;
                }
                
                // Opfer wegschleudern
                DebugLog("%s", procedure);
                Fling(victim, direction * (3 + booster), iYDir);
            }
        }
    }
    else
    {
        // leichten Blut-Effekt hinzufügen
        var x = GetX(victim) - GetX();
        var y = GetY(victim) - GetY();

        for (var i = 0; i < 3; i++)
        {
            var xDir = Random(10) * -direction;
            var yDir = RandomX(-10, 10);
            var s = 50 + Random(30);
            CreateParticle("EkeBlood", x, y, xDir, yDir, s);

            if (punch < 5) break; // Shotgun
        }
        // nicht bei schweren (großen) Lebewesen
        if (GetMass(victim) < 500)
        {
            // Lebewesen wird je nach Flugzeit weggedrückt
            for (var i = 0; i < (5 - flightTime); i++)
            {
                if (punch < 5) if (Random(3)) break; // Shotgun

                // Opfer aber dabei nicht in Wände hineindrücken
                var besideWall = GetContact(victim, -1) & (((direction + 1) / 2) + 1);
                if (!besideWall) SetPosition(GetX(victim) + direction, GetY(victim), victim, 1);
            }
        }
    }
    // Sound abspielen und Kugel entfernen
    Sound("BU_FleshHit*", 0, victim, 50);
    RemoveObject();
    return(1);
}

func HitBalloon(victim)
{
    if ((GetID(victim) != BALN) && (GetID(victim) != BLMP)) return(0);

    victim -> Poke();
    RemoveObject();
    return(1);
}

func HitTin(victim)
{
    var b1 = GetID(victim) == GR7A;
    var b2 = ObjectCount(NF7A);
    var b3 = !Hostile(GetController(), GetController(victim), 1);

    if (b1 && b2 && b3)                         return(0);
    if (GetOCF(victim) & OCF_Alive)             return(0);
    if (GetCategory(victim) & C4D_StaticBack)   return(0);
    if (GetCategory(victim) & C4D_Structure)    return(0);
    if (PrivateCall(victim, "IsTree"))          return(0);
    if (!PrivateCall(victim, "Damage"))         return(0);

    SetController(GetController(), victim);
    DoDamage(1, victim);

    Sound("BU_TinHit*");
    RemoveObject();
    return(1);
}

// wird bei Kontakt von allen Seiten aufgerufen
// ist nur Left weil das CNAT auf Left steht
func ContactLeft()
{
    // beim normalen Aufruf von Hit aus der Engine wäre die Kugel schon entlang der Wand hoch oder hinunter geschlittert
    // bei Contact noch nicht
    Hit();
}