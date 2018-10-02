/* Benzin */

#strict

func Activate(object clonk)
{
  for (var i = 0; i < 5; i++) 
  {
    CreateContents(MO7A, clonk);
  }
  ShiftContents(clonk, true, MO7A);
  Sound("FT_Reload");
  RemoveObject();
  return(1);
}

func BlowUp()
{
  CastObjects(DFLM, 50, 50);
  Explode(50);
  return(1);
}   

func Damage()
{  
  if (GetDamage() < 5) return(1);
  ScheduleCall(0, "BlowUp", 1);
  return(1);
}

func ContactBottom()
{
  if (GetYDir() < 100) return(0);
  ScheduleCall(0, "BlowUp", 1);
  return(1);
}

func Hit()
{
  Sound("ClonkHit*");
  return(1);
}