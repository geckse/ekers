#strict 2
#appendto ST5B

func Initialize() {
    AddEffect("Hobble", this, 1, 2, this);
    return _inherited(...);
}
func FxHobbleTimer()
{ 
  if (GetY() < 210) Incinerate();
  return _inherited(...);
}

//Hier sollten Stippel keine Kokons legen
func Pregnancy() 
{
  if(GetID() == ST5B) return false;
  return _inherited(...);
}