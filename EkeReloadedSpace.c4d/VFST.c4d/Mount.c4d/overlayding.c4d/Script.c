/* Mount */

#strict

protected func Initialize()
{
  SetVisibility(VIS_Owner);
  SetPosition(54, 104);
  return(1);
}

protected func Check(){
if(!GetCrew(GetOwner())) return;
  var cu = GetCursor(GetOwner());


  if(!cu || !cu->~IsClonk()) return;

  if(Frozen(cu)){
    SetGraphics("freeze");
  } else {
    SetGraphics();
  }

  if(FindObject(META) && cu){
     if(cu->~GBackSolid(0,12) || cu->~GetAction() S= "Hangle" || cu->~GetAction() S= "Scale"){
        if((cu->~GetFuel()) < (cu->~MaxFuel()) ){
           if(GetAction() ne "Ani") SetAction("Ani");
        }
      } else {
        if(GetAction() ne "Noe") SetAction("Noe");
      }
     } else {
       if(GetAction() ne "Noe")  SetAction("Noe");
     }
  }