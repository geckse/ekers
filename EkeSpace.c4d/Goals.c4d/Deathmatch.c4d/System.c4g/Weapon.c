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
            CustomMessage("<c 77adca>Spawnschutz</c>", container, GetOwner(container), 0, -15);
            return false;
        }   
    }
    return _inherited(...);
}