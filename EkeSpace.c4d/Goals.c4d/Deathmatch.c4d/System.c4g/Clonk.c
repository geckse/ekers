#strict 2
#appendto SF7A

func Initialize()
{
    if(!goal_dm) return _inherited(...);

    AddSpawnProtection(150);

    var ret = _inherited(...);

    SpawnClonk(this);

    return ret;
}