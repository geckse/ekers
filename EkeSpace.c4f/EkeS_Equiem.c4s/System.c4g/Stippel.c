#strict 2
#appendto ST5B

func Initialize() {
    AddEffect("Hobble", this, 1, 2, this);
    return _inherited(...);
}
func FxHobbleTimer()
{ 
  if (GetY() < 210) Kill();
  if (ObjectCount(ST5B) > 15) Kill();
  return _inherited(...);
}