/* Patronen */

#strict 2

func SplitID() { return PM7A; }
func SplitAmount() { return 5; }
func HitSound() { return "RockHit*"; }

func Activate(object clonk)
{
  CreateContents(SplitID(), clonk, SplitAmount());
  ShiftContents(clonk, true, SplitID());
  Sound("SF_Process");
  RemoveObject();
  return true;
}

func Hit()
{
	Sound(HitSound());
  return true;
}