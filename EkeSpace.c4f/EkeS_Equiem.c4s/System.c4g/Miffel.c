#strict 2
#appendto MI5B

func Initialize() {
    AddEffect("Hobble", this, 1, 2, this);
    return _inherited(...);
}
func FxHobbleTimer()
{ 
  if (GetY() < 210) Incinerate();
  return _inherited(...);
}