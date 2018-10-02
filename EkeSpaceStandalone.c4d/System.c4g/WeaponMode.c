#strict 2

#appendto AR7A

local iSwitch;

func Initialize() {
  iSwitch = 0;
  return _inherited(...);
}

func ControlThrow(object clonk)
{  
  if(iSwitch) {
	  iSwitch = 0;
  }
  else {
	  iSwitch = 1;
	  AddEffect("Switch", this, 1, 2, this);
  }
  // ControlShoot();
  return(1);
}

func PilotLight()
{
  var clonk = Contained();
  var dir = GetDir(clonk);

  if (!WildcardMatch(GetAction(clonk), "AssaultRifle*")) return(0);

  var x = 20 * dir - 10 + Random(2);
  var y = RandomX(-3, -1);

  CreateParticle("PSpark", x, y, 0, -1, 20, GetColorDw(clonk), clonk);
  CreateParticle("PSpark", x, y, 0, 0, 20, RGBa(255,255,255,120), clonk);
  return(1);
}

func IsShooting()
{
	return GetAction() == "Shoot";
}

func FxSwitchTimer()
{	
	if(iSwitch) {
		if(!IsShooting()) PilotLight();
		AddEffect("Switch", this, 1, 2);
	}
	else {
		return(-1);
	}
}