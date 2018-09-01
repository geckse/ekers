/* Mount */

#strict

protected func Initialize()
{
  SetVisibility(VIS_Owner);
  SetPosition(72, 104);
  return(1);
}

protected func Check(){
if(!GetCrew(GetOwner())) return;
  var cu = GetCursor(GetOwner());


  if(!cu || !cu->~IsClonk()) return;


}