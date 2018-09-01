/*-- Neues Script --*/

#strict
#appendto RL5B

func ControlLeft(object clonk)
{
  if (!guiding) return(0);

  SetPlrView(GetOwner(clonk), missile);
  LocalN("command", missile) = "Left";
  clonk->~SetComDir(COMD_Stop());
        Schedule("SetComDir(COMD_Stop(),this)",1,1,clonk);
  return(1);
}

func ControlRight(object clonk)
{
  if (!guiding) return(0);

  SetPlrView(GetOwner(clonk), missile);
  LocalN("command", missile) = "Right";
  clonk->~SetComDir(COMD_Stop());
       Schedule("SetComDir(COMD_Stop(),this)",1,1,clonk);
  return(1);
}
func IsGuided(){ if(missile) return(guiding); }