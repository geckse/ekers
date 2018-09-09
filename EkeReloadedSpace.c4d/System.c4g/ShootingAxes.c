/*-- shooting axes --*/

#strict 2
#appendto AR5B
#appendto PT5B
#appendto SG5B
#appendto UZ5B

func ControlDigSingle()
{  
    return(1);
}
func ControlDig(object clonk)
{    
    clonk -> SwitchShootingAxis();
    return(1);
}
func CreateBullet(dir, clonk)
{
    var iAxis = clonk -> GetShootingAxis();
    var x = 8 * dir - 4;

    // set bullet spawnpoint depending on axis
    var y = 0;
    if (iAxis == 2) {
        y = 4;
    }
    else if (iAxis == 3) {
        y = -4;
    }

    var bullet = CreateObject(BU5B, x, y, NO_OWNER);
    bullet -> SetAxis(iAxis);
    bullet -> Launch(this(), dir, clonk);
    SetController(GetController(clonk), bullet);
    return(bullet);
}

// prevent axis change on reload
func Activate(object clonk)
{
    clonk -> SwitchShootingAxis();
    clonk -> SwitchShootingAxis();
    return(_inherited(Par(), Par(1)));
}