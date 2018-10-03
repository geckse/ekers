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
  Stop();
  return(1);
}

func PilotLight()
{
  var clonk = Contained();
  var dir = GetDir(clonk);

  if (!WildcardMatch(GetAction(clonk), "AssaultRifle*")) return(0);

  var x = 16 * dir - 8 + Random(2);
  var y = -1;

  CreateParticle("PSpark", x, y, 0, -1, 20, GetColorDw(clonk), clonk);
  CreateParticle("PSpark", x, y, 0, 0, 20, RGBa(255,255,255,120), clonk);
  return(1);
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