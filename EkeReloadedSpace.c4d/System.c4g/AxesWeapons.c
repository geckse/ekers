/*-- Bullet Axes --*/

#strict 2
#appendto AR5B
#appendto PT5B
#appendto SG5B
#appendto UZ5B

local iBulletAxis;

// change shooting axis by pressing "dig"
func ControlDigSingle()
{  
    return(1);
}
func ControlDig()
{
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

    // Startpunkt der Kugel festlegen
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
  bullet -> Launch(this(), dir, clonk);
  bullet -> GetAxis(iBulletAxis);
  SetController(GetController(clonk), bullet);
  return(1);
}