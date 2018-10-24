#strict 2
#appendto WP7A

local container;

func ControlShoot()
{
    if(deathmatchRule)
    {
        container = Contained();
        if (GetEffect("SpawnProtection", container))
        {
            Stop();
            ScheduleCall(0, "SpawnMessage", 1);
            return false;
        }   
    }
    return _inherited(...);
}

func SpawnMessage()
{
    CustomMessage("<c 77adca>Spawnschutz</c>", container, GetOwner(container), 0, -15);
}