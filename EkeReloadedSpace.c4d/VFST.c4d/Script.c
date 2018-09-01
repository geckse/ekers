/*--Raumfahrer Clonk--*/

#strict 2
#include SF5B
#include JB4K

local iO2;

func MaxO2(){ return(100); }

func Initialize(){
  iO2 = MaxO2();
  AddEffect("Life", this(), 1, 35, this());

  return(_inherited());
}

protected func ContactBottom()
  {
  if (GetAction() == "Swim" || WildcardMatch(GetAction(), "*Swim") )
    SetAction("Walk");
  return(1);
  }


func DoO2(val){
   iO2 += val;
   if(iO2 >= MaxO2()) iO2 = MaxO2();
   if(iO2 < 0) iO2 = 0;
   return iO2;
}
func SetO2(val){
   iO2 = val;
   if(iO2 >= MaxO2()) iO2 = MaxO2();
   if(iO2 < 0) iO2 = 0;
   return iO2;
}
func GetO2(){
   return iO2;
}

/*Essen und Schlafen*/
func FxLifeTimer()
{
  if(!GetAlive()) return(-1);

  AddEffect("Life", this(), 1, 35);//wiederholen

  if(FindObject(NDO2)){
   DoO2(-1);

   if(GetO2() <= 0){
      DoEnergy(-2);
   }
  }

  if(FindObject(META)){
     if(GBackSolid(0,12) || GetAction() == "Hangle" || GetAction() == "Scale"){
        if(GetFuel() < MaxFuel()){
          for(var i = 0; i < 34; i++){
           Schedule("this->~DoFuel(12)",i+1,1);
          }
         }
     }
  }

}

func FxLifeStop()
{
  return(1);
}

protected func Collection2(stuff)
{
  if (ContentsCount(GetID(stuff)) == 1)
  {
    // hinten an die Inventarliste hängen
    if (GetID(stuff) != PT5B) ShiftContents();
  }
  // Bewaffnung prüfen
  CheckArmed();
  return(1);
}