/*-- Very Special Forces Trooper --*/

#strict 2
#include SF5B
#include JB4K

local iO2;
local iTemp;
local iShootingAxis;
local pCrosshair;

func MaxO2(){ return(100); }

func Initialize(){
  iO2 = MaxO2();
  AddEffect("Life", this(), 1, 35, this());
  iShootingAxis = 1;
  CreateCrosshair();
  AddEffect("Crosshair", this(), 1, 1, this());
  return(_inherited());
}

protected func ContactBottom()
  {
  if (GetAction() == "Swim" || WildcardMatch(GetAction(), "*Swim") )
    SetAction("Walk");
  return(1);
  }

/* -- luft -- */

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

/* -- temperatur -- */

func GetTemperature(){
   return iTemp;
}
func DoTemperature(val){
   iTemp += val;
   if(iTemp >= 100) iTemp = 100;
   if(iTemp < -100) iTemp = -100;
   return iTemp;
}
func SetTemperature(val){
   iTemp = val;
   if(iTemp >= 100) iTemp = 100;
   if(iTemp < -100) iTemp = -100;
   return iTemp;
}

/*Essen und Schlafen*/
func FxLifeTimer()
{
  if(!GetAlive()) return(-1);

  AddEffect("Life", this(), 1, 35); //wiederholen

  // Lebensysteme Kühlung bekämpfen
  if(iTemp < 37) DoTemperature(+1);
  if(iTemp < 18) DoTemperature(+1);
  if(iTemp < -20) DoTemperature(+2);
  if(iTemp < -40 && !Frozen(this()) ) AddEffect("Freeze", this(), 111, 5, 0, FREZ, GetController(this()));

  // und Hitze
  if(iTemp > 39) DoTemperature(-1);
  if(iTemp > 60) DoTemperature(-1);
  if(iTemp > 80) DoTemperature(-2);

  if(OnFire(this())) DoTemperature(+10);

  if(FindObject(HEFR)){
    if(GetY() < ObjectCount(HEFR)*100){
      DoTemperature(-RandomX(12,19));
      CreateParticle("Freeze",0,0,0,0,14*5+20,RGB(0,40,80),this());
      CreateParticle("Freeze",0,0,0,0,3*5+20,RGB(0,40,80),this());

      for(var i = 0; i < 5; i++){
        CreateParticle("NoGravSpark",RandomX(-24/2, 24/2),RandomX(-24/2, 24/2),0,RandomX(-2, -4),RandomX(18,28),RGB(10,120,210), this());
      }

    }
  }

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
           Schedule("this->~DoFuel(18)",i+1,1);
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

/*------------------------------------*\
    Shooting Axis + Crosshair
\*------------------------------------*/
func GetShootingAxis(){
    return(iShootingAxis);
}
func SwitchShootingAxis(){
    iShootingAxis++;
    if (iShootingAxis > 3) {
        iShootingAxis = 1;
    }
    UpdateCrosshairPosition();
    return(1);
}
func CreateCrosshair() {
    pCrosshair = CreateObject(CH7A, 0, 0, GetOwner(this())); pCrosshair->SetAction("Crosshair", this());
    UpdateCrosshairPosition();
    return(1);
}
func UpdateCrosshairPosition() {

    // set x
    var iDir = GetDir() * 2 - 1; // is -1 or 1
    var x = -40 * iDir;

    // set y
    var y = -5;
    if (iShootingAxis == 2) {
      y = -23;
    } else if (iShootingAxis == 3) {
      y = 17;
    }

    // set position
    SetVertexXY(0,x,y,pCrosshair);

    return(1);
}
func Entrance() {
    RemoveObject(pCrosshair);
    return(_inherited());
}
func Departure() {
    CreateCrosshair();
    return(_inherited());
}
func CrewSelection(deselect)
{
    if(deselect) {
      SetVisibility(VIS_None, pCrosshair);
    } else {
      SetVisibility(VIS_Owner, pCrosshair);
      UpdateCrosshairPosition();
    }
    return(_inherited());
}
protected func Death()
{

  RemoveObject(pCrosshair);

  // ggf. HUD entfernen
  CrewSelection(true);

  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this(), GetKiller());

  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return(0);

  Sound("SF_Die");
  DeathAnnounce();

  // Letztes Mannschaftsmitglied tot?
  if (!GetCrew(GetOwner())) GameCallEx("RelaunchPlayer", GetOwner(), this());

  // Tod dem Spiel(ziel) berichten
  GameCallEx("ReportHomicide", GetKiller(), GetOwner(), GetID(this));
  return(1);
}

// crosshair update effect
func FxCrosshairTimer() {
    UpdateCrosshairPosition();
}