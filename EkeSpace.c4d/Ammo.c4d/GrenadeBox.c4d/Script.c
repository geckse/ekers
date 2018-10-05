/* Granaten */

#strict

func Activate(object clonk)
{
  for (var i = 0; i < 3; i++) 
  {
    CreateContents(HG7A, clonk);
  }
  ShiftContents(clonk, true, HG7A);
  Sound("SF_Process");
  RemoveObject();
  return(1);
}

func Hit()
{
  Sound("WoodHit*");
  return(1);
}