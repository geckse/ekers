/* Mount */

#strict

local doTimer;

protected func Initialize()
{
  SetVisibility(VIS_Owner);
  SetPosition(55, 131);
  SetAction("Fill");
  return(1);
}

func Check(){
if(!GetCrew(GetOwner())) return;
 if(!GetCursor(GetOwner())) return;
 if(!GetCursor(GetOwner())->~GetO2()) return;
 var cu = GetCursor(GetOwner());

  if(!cu || !cu->~IsClonk()) return;

 var perc = (cu->~GetO2()*100)/cu->~MaxO2();

 SetPhase(9-(perc/10));

 if(GetPhase() >= 8){
   Sound("Warning_lowoxygen",1,cu,100,GetOwner()+1);
 }

 if(GetPhase() == 8){
   doTimer++;
   if(doTimer >= 7){
      SetPhase(9);
   }
   if(doTimer >= 12){
      doTimer = 0;
   }
 }

}