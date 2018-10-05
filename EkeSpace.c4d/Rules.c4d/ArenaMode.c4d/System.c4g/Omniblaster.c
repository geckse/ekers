#strict 2
#appendto OB7A

/*------------------------------------------*\
    Change Owner On Collect
\*------------------------------------------*/
func Entrance(object container)
{
    if(arenaModeRule)
    {
        if (GetAlive(container) && mode != "Enemy") SetOwner(GetOwner(container));
    }
    return(_inherited(container, ...));
}
