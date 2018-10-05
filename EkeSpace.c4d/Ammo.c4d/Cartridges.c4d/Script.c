/* Patronen */

#strict

func Activate(object clonk)
{
  for (var i = 0; i < 5; i++) 
  {
    CreateContents(PM7A, clonk);
  }
  ShiftContents(clonk, true, PM7A);
  Sound("SF_Process");
  RemoveObject();
  return(1);
}

func Hit()
{
  Sound("RockHit*");
  return(1);
}