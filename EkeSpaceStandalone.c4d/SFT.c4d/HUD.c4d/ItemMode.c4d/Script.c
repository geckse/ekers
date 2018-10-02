/* HUD */

#strict

local mode;

protected func Initialize()
{
  SetVisibility(VIS_None);
  SetAction("RollIn");
  return(1);
}

public func Scroll(newMode, fast)
{
  if ((mode == newMode) && !fast) return;
  
  mode = newMode;
  
  if (fast)
  {
    SetGraphics(mode);
    SetAction("RollIn");
    SetPhase(7);
  }
  else
  {
    if (GetAction() eq "RollOut") return(ChangeMode());
    SetAction("RollOut");
  }
  return(1);
}

private func ChangeMode()
{
  SetGraphics(mode);
  SetAction("RollIn");
  return(1);
}

protected func AttachTargetLost()
{
    RemoveObject();
}
