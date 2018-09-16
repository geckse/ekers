/*-- shooting axes --*/

#strict 2
#appendto AR5B
#appendto PT5B
#appendto SG5B
#appendto UZ5B

static const ShootingAxis_Straight = 1;
static const ShootingAxis_Downwards = 2;
static const ShootingAxis_Upwards = 3;

func CreateBullet(dir, clonk)
{
    var iAxis = clonk -> GetShootingAxis();
    var x = 8 * dir - 4;

    // set bullet spawnpoint depending on axis
    var y = 0;
    if (iAxis == ShootingAxis_Downwards) {
        y = 4;
    }
    else if (iAxis == ShootingAxis_Upwards) {
        y = -4;
    }

    var bullet = CreateObject(BU5B, x, y, NO_OWNER);
    bullet -> SetAxis(iAxis);
    bullet -> Launch(this(), dir, clonk);
    SetController(GetController(clonk), bullet);
    return(bullet);
}
func CreateGrenade(dir, clonk)
{
    var iAxis = clonk -> GetShootingAxis();
    var x = 8 * dir - 4;
    var xDir = 20 * dir - 10;

    // set grenade spawnpoint depending on axis
    var y = 0;
    var yDir = -1;
    if (iAxis == ShootingAxis_Downwards) {
        y = 4;
    }
    else if (iAxis == ShootingAxis_Upwards) {
        y = -4;
    }

  // set grenade direction depending on axis
  var yDir = -1 + y;

  var grenade = CreateContents(GR5B);
  Exit(grenade, x, y, 0, xDir, yDir);
  grenade -> Launch(clonk);
  SetController(GetController(clonk), grenade);
  return(1);
}

func ControlThrow(object clonk, bool really)
{
  if(really)
  {
    return _inherited(clonk, ...);
  }
  return true;
}

func IsWeapon()
{
  return true;
}

func IsShooting()
{
	return GetAction() == "Shoot";
}