/*-- Energy Bar --*/

#strict 2

protected func Initialize() 
{
  SetVisibility(VIS_None);
  return true;
}
protected func AttachTargetLost()
{
    RemoveObject();
}
