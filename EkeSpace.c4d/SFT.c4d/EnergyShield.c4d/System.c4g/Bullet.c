#strict 2
#appendto BU7A

local xStart;
local yStart;

func Launch()
{
    xStart = GetX();
    yStart = GetY();

    return _inherited(...);
}

func HitCreature(victim)
{
    if(victim->~GetShieldEnergy())
    {
          var p1 = GetController();
          var p2 = GetController(victim);

          if (ObjectCount(NF7A) && !Hostile(p1, p2, 1)) return(0); // kein Friendly Fire
          if (!GetAlive(victim))                        return(0); // Opfer muß noch leben
          if (GetID(victim) == ZAP1)                    return(0); // Zaps nicht beachten

          // dem Opfer Energie abziehen
          DoEnergy(-punch, victim);
          victim->~HitShieldFrom(xStart, yStart);

          // Sound abspielen und Kugel entfernen
          Sound("BU_SoftHit*", 0, victim, 50);
          RemoveObject();
          return 1;
    }
    return _inherited(victim,...);
}