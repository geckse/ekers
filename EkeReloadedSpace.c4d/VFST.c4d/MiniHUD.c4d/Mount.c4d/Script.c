/* Mount */

#strict

protected func Initialize()
{
  SetVisibility(VIS_Owner);
  return(1);
}
protected func AttachTargetLost()
{
    RemoveObject();
}
