#strict 2
#appendto JB4K

/*------------------------------------*\
    Fuel Regeneration
\*------------------------------------*/
func Consumption(){
  if(!arenaModeRule){ return 5; } else { return 20; }
}

private func Active() {
  if(!arenaModeRule) return _inherited(...);
  RemoveEffect("FuelRegen",this);
  return _inherited(...);
}

private func StandBy() {
  if(!arenaModeRule) return _inherited(...);
  AddEffect("FuelRegen", this, 1, 2, this);
  return _inherited(...);
}

protected func FxFuelRegenTimer()
{
  if(GetProcedure() == "WALK" || GetProcedure() == "HANGLE" || GetProcedure() == "SCALE") DoFuel(70);
}