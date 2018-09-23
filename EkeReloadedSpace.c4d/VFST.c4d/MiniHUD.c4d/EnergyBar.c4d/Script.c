/*-- Energy Bar --*/

#strict 2

protected func Initialize() 
{
  SetVisibility(VIS_Owner);
  return true;
}
protected func AttachTargetLost()
{
    RemoveObject();
}
