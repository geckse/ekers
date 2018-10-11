#strict 2
#appendto HG7A

/*------------------------------------------*\
    Change Owner On Collect
\*------------------------------------------*/
func Entrance(object container)
{
    if(arenaModeRule) SetOwner(GetOwner(container));
    return(_inherited(container, ...));
}
