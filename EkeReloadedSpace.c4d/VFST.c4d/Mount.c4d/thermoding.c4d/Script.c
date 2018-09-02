/* Mount */

#strict

local pPointer;

protected func Initialize()
{
  SetVisibility(VIS_Owner);
  SetPosition(72, 104);

  pPointer = CreateObject(ND4B,72,104,GetOwner());

  return(1);
}

protected func Check(){
if(!GetCrew(GetOwner())) return;
  var cu = GetCursor(GetOwner());

  if(!cu || !cu->~IsClonk()) return;

  if(cu->~GetTemperature() > 0) pPointer->SetPosition(72,104-(cu->~GetTemperature() /6 ) );
  if(cu->~GetTemperature() < 0) pPointer->SetPosition(72,104-(cu->~GetTemperature() /6 ) );

}
