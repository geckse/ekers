/* Mount */

#strict

local pDeko;
local pAir;
local pThermo;

protected func Initialize()
{
  SetVisibility(VIS_Owner);
  SetPosition(55, 104);

  SetAction("Fill");

  //pDeko = CreateObject(MT2B,0,0,GetOwner());
  //pAir = CreateObject(MT3B,0,0,GetOwner());
  //pThermo = CreateObject(MT4B,0,0,GetOwner());
  RemoveObject(this);
  return(1);
}

func Check(){
 if(!GetCrew(GetOwner())) return;
 if(!GetCursor(GetOwner())) return;
 if(!GetCursor(GetOwner())->~GetFuel()) return;
 var cu = GetCursor(GetOwner());

  if(!cu || !cu->~IsClonk()) return;

 var perc = (cu->~GetFuel()*100)/cu->~MaxFuel();

 SetPhase(40-(perc/2));
 if( (perc < 25 && cu->~IsActive() && FindObject(META)) || (perc < 10 && cu->~IsActive() && !FindObject(META)) ){
   Sound("doum",1,cu,100,GetOwner()+1);
 }

    // Mini HUD: Fuel Bar
    cu->~SetFuelLevel(perc);
}