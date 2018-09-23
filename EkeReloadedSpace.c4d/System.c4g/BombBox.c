#strict 2
#appendto BB5B

func Activate(object clonk)
{
  for (var i = 0; i < 2; i++) 
  {
    CreateContents(OB5B, clonk);
  }
  ShiftContents(clonk, true, OB5B);
  Sound("SF_Process");
  RemoveObject();
  return(1);
}