/*-- Very Special Forces Trooper --*/

#strict 2
#include SF5B
#include JB4K

local iO2;
local iTemp;
local iShootingAxis;

local clonkName;

local lifeBar;
local lifeBarBackground;
local ammoBar;
local ammoBarBackground;
local fuelBar;
local fuelBarBackground;
local energyBarsX;

func MaxO2(){ return(100); }

func Initialize(){
  iO2 = MaxO2();
  AddEffect("Life", this(), 1, 35, this());
  iShootingAxis = 1;
  energyBarsX = -8;
  CreateEnergyBars();
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
    Shooting Axis
\*------------------------------------*/
func GetShootingAxis(){
    return(iShootingAxis);
}
func SwitchShootingAxis(){
    iShootingAxis++;
    if (iShootingAxis > 3) {
        iShootingAxis = 1;
    }
    return(1);
}
func ControlAxis(int newAxis){
    var weapon = Contents();
    if(newAxis != iShootingAxis) {
      iShootingAxis = newAxis;

      if(weapon && weapon->~IsWeapon() && !weapon->~IsShooting()) {
        weapon->ControlThrow(this, true);
      }
    } else {
      if(weapon && weapon->~IsWeapon()) {
        weapon->ControlThrow(this, true);
      }
    }
}
protected func Death()
{
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

/*------------------------------------*\
    Nameless Hero
\*------------------------------------*/
func WipeName() {
    SetName("");
}
func ResetName() {
    SetName(clonkName);
}
func DisplayRealName() {
    CustomMessage(Format("@%s|%s", $ClonkRanks$[GetRank(this())] ,clonkName), 0, GetOwner(), -5,55, 0, 0, "1", 1);
    return(1);
}
func DeathAnnounce () {
    Message("%s $DeathMsg$", this(), clonkName);
    return(1);
}
func Recruitment()
{
  clonkName = Format("%s", GetName());
  WipeName();
  return(_inherited());
}
func CrewSelection(deselect)
{
    if(!deselect) {
        DisplayRealName();
    }
    return(_inherited());
}

/*------------------------------------*\
    Mini Hud
\*------------------------------------*/
func RemoveHud() {
    RemoveObject(lifeBar);
    RemoveObject(ammoBar);
    RemoveObject(fuelBar);
}
func CreateEnergyBars() {
    CreateLifeBar();
    CreateAmmoBar();
    CreateFuelBar();
    AddEffect("Energy", this(), 1, 2, this);
}
func FxEnergyTimer()
{
  if(!GetAlive()) return(-1);

  AddEffect("Energy", this(), 1, 2); //wiederholen

  // update life bar
  UpdateEnergyBar(lifeBar, GetEnergy());

  // update fuel bar
  var perc = (GetFuel()*100)/MaxFuel();
  UpdateEnergyBar(fuelBar, perc);
  if(perc < 33 && IsActive()) {
    Sound("doum",1,this,100,GetOwner()+1); 
  }
}
func UpdateEnergyBar(object pEnergyBar, int iEnergy) {
    SetPhase(iEnergy, pEnergyBar);
}

// Mode Switch
private func ScrollHud(mode, fast)
{  
  var owner = GetOwner(this());
  if (GetCursor(owner) != this()) return;

  var hud = FindObjectOwner(HU7A, owner);
  if(!hud)
  {
    // Halterung erzeugen
    var modeSwitch = CreateObject(MT7A, 0, 0, owner);
    SetVertexXY(0,18,16,modeSwitch);
    SetObjDrawTransform(667,0,0,0,667,0,modeSwitch);
    modeSwitch -> SetAction("Attach", this);

    // Modus-Dreh-Bildchen erzeugen
    hud = CreateObject(HU7A, 0, 0, owner);
    SetVertexXY(0,18,16,hud);
    SetObjDrawTransform(667,0,0,0,667,0,hud);
    hud -> SetAction("Attach", this);
  }
    
  hud -> Scroll(mode, fast);
  return(1);
}

// Life Bar
func CreateLifeBar() {
    lifeBarBackground = CreateObject(EB7A,0,0,GetOwner());
    lifeBar = CreateObject(EB7A,0,0,GetOwner());
    
    SetVertexXY(0,energyBarsX,22,lifeBar);
    SetVertexXY(0,energyBarsX,22,lifeBarBackground);
    SetClrModulation(RGBa(202,119,119,0), lifeBar);
    SetGraphics("Overlay", lifeBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
    SetGraphics("Background", lifeBarBackground);
    
    lifeBar -> SetAction("Attach", this);
    lifeBarBackground -> SetAction("Attach", this);
}

// Ammo Bar
func CreateAmmoBar() {
    ammoBarBackground = CreateObject(EB7A,0,0,GetOwner());
    ammoBar = CreateObject(EB7A,0,0,GetOwner());
    
    SetVertexXY(0,energyBarsX,16,ammoBar);
    SetVertexXY(0,energyBarsX,16,ammoBarBackground);
    SetClrModulation(RGBa(119,173,202,0), ammoBar);
    SetGraphics("Overlay", ammoBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
    SetGraphics("Background", ammoBarBackground);
    
    ammoBar -> SetAction("Attach", this);
    ammoBarBackground -> SetAction("Attach", this);
}
private func SetAmmoBar(int percent)
{
  ResetPhysical();
  DoMagicEnergy(0);

  SetPhysical("Magic", 100000, 2);
  DoMagicEnergy(percent);
  UpdateEnergyBar(ammoBar, percent);
}

// Fuel Bar
func CreateFuelBar() {
    fuelBarBackground = CreateObject(EB7A,0,0,GetOwner());
    fuelBar = CreateObject(EB7A,0,0,GetOwner());
    
    SetVertexXY(0,energyBarsX,10,fuelBar);
    SetVertexXY(0,energyBarsX,10,fuelBarBackground);
    SetClrModulation(RGBa(119,202,146,0), fuelBar);
    SetGraphics("Overlay", fuelBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
    SetGraphics("Background", fuelBarBackground);
    
    fuelBar -> SetAction("Attach", this);
    fuelBarBackground -> SetAction("Attach", this);
}