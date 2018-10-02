/* Bombenkiste */

#strict

func Activate(object clonk)
{
  for (var i = 0; i < 3; i++) 
  {
    CreateContents(OB7A, clonk);
  }
  ShiftContents(clonk, true, OB7A);
  Sound("SF_Process");
  RemoveObject();
  return(1);
}

func Hit()
{
  Sound("RockHit*");
  return(1);
}