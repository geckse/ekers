/* HUD */

#strict

local mode;

protected func Initialize()
{
  SetVisibility(VIS_Owner);
  SetAction("RollIn");
  return(1);
}

public func Scroll(newMode, fast)
{
  if ((mode == newMode) && !fast) return;
  
  if (newMode == "Biomap")
  {
    // Biomap erzeugen
    ActivateBiomap();
  }
  else
  {
    // Biomap entfernen
    var biomap = FindObjectOwner(BM5B, GetOwner());
    if (biomap) RemoveObject(biomap);
  }
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

private func ActivateBiomap()
{
  var owner = GetOwner(this());
  CreateObject(BM5B, 0, 0, owner);

  Sound("SF_Biomap", 0, GetCursor(owner));
  return(1);
}
protected func AttachTargetLost()
{
    RemoveObject();
}
