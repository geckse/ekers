/* Neohexin */

#strict

func Activate(object clonk)
{
  var breath = GetPhysical("Breath", 0, clonk) / 1000;
  var energy = GetPhysical("Energy", 0, clonk) / 1000;

  var b1 = OnFire(clonk);
  var b2 = GetBreath(clonk) < breath;
  var b3 = GetEnergy(clonk) < energy;

  if (b1 || b2 || b3)
  {
    Extinguish(clonk);

    DoBreath(breath, clonk);
    DoEnergy(energy, clonk);

    Sound("NH_Energy");
    RemoveObject();
  }
  return(1);
}

func Hit()
{
  Sound("MetalHit*");
  return(1);
}