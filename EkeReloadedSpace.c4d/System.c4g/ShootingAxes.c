/*-- shooting axes --*/

#strict 2
#appendto AR5B
#appendto PT5B
#appendto SG5B
#appendto UZ5B

local iBulletAxis;

func ControlDigSingle()
{  
    return(1);
}
func ControlDig()
{
    // initialize axis
    if (!iBulletAxis) {
        iBulletAxis = 1;
    }
    
    // switch axis
    iBulletAxis++;
    if (iBulletAxis > 3) {
        iBulletAxis = 1;
    }
    return(1);
}
func CreateBullet(dir, clonk)
{
    var x = 8 * dir - 4;
    var y = 0;

    // set bullet spawnpoint depending on axis
    if (iBulletAxis == 1) {
        y = 0;
    }
    else if (iBulletAxis == 2) {
        y = 4;
    }
    else if (iBulletAxis == 3) {
        y = -4;
    }
    else {
        y = 0;
    }

    var bullet = CreateObject(BU5B, x, y, NO_OWNER);
    bullet -> GetAxis(iBulletAxis);
    bullet -> Launch(this(), dir, clonk);
    SetController(GetController(clonk), bullet);
    return(bullet);
}