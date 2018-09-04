/* Granaten */

#strict

func Activate(object clonk)
{
  for (var i = 0; i < 5; i++) 
  {
    CreateContents(HG5B, clonk);
  }
  ShiftContents(clonk, true, HG5B);
  Sound("SF_Process");
  RemoveObject();
  return(1);
}

func Hit()
{
  Sound("WoodHit*");
  return(1);
}