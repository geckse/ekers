/* Sprengpfeil */

#strict

local shooter;

func Launch(clonk)
{
  shooter = clonk;
  SetAction("Fly");
  return(1);
}
  
func Flying()
{
  if (EkeFindVictim(-10, -10, 20, 20, shooter)) return(BlowUp());
  SetR(Angle(0, 0, GetXDir(), GetYDir()));
}

func BlowUp()
{
  Schedule("Explode(20)", 1);
  return(1);
}    

func Hit()
{
  return(BlowUp());
}

func Damage()
{
  if (GetDamage() < 1) return(1);
  return(BlowUp());
}