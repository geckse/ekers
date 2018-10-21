#strict 2
#appendto WP7A

func ControlShoot()
{
    if(deathmatchRule)
    {
        var container = Contained();
        if (GetEffect("Spawn", container))
        {
            Stop();
            Message("<c 77adca>Spawnschutz</c>", container);
            return false;
        }   
    }
    return _inherited(...);
}