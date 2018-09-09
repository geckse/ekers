/*-- Crosshair --*/

#strict

protected func Initialize()
{
  SetVisibility(VIS_Owner());
}
func AttachTargetLost() {
    RemoveObject();
}