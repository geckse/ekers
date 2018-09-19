/*-- Spawn Protection --*/

#strict 2
#appendto BU5B

func HitCreature(victim)
{
    if (GetEffect("Spawn") || GetEffect("Spawn", victim)) return(0);
	return(_inherited(Par(0), Par(1)));
}