/*-- Crosshair --*/

#strict 2

protected func Initialize()
{
    SetVisibility(VIS_None);
}
func AttachTargetLost() {
    RemoveObject();
}