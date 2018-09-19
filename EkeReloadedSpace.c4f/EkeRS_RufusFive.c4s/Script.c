 /*-- Rufus V --*/

#strict 2

static clonkSpawns;
static clonkSpawnsL;

func Initialize() {

  // declare clonk respawn points
  clonkSpawns = [
      [0207, 0538],
      [1843, 0328],
      [1058, 0299],
      [0750, 0699],
      [1380, 0499],
      [0580, 0499],
      [1873, 0547]
  ];
  clonkSpawnsL = GetLength(clonkSpawns);

  // Sky
  SetSkyParallax (0,17,19,0,0,0,0); 
  SetGamma(RGB(15,15,15),RGB(118,118,118),RGB(215,215,215));

  // Fog
  for(var i=0;i<180;++i) 
    CreateParticle("Fog",Random(LandscapeWidth()),Random(LandscapeHeight()),0,0,RandomX(900,1700));
  
  CreateObject(COFA);
  CreateItemSpawns();
  CreateStalactites();
  return(ScriptGo(1));
}
func Script1()
{
  SetMaxPlayer();
  return(1);
}

func Script2(){
    for(var spwn in FindObjects(Find_ID(SPNP))) {
    var Contents = [CA5B, OB5B, HG5B, GB5B, NH5B, GS5B, SG5B];
    CreateContents(Contents[Random(GetLength(Contents))], spwn);
   }
}
func Script120(){
     goto(2);
}

private func InitializeClonk(clonk)
{ 
    // move new clonk to random respawn point
    var r = Random(clonkSpawnsL);
    SetPosition(clonkSpawns[r][0], clonkSpawns[r][1], clonk);

    // add spawn protection
    AddEffect("Spawn",clonk,20,1);
  
    var assaultRifle = CreateContents(AR5B, clonk);
    LocalN("ammo", assaultRifle) = 100;
    LocalN("qGrenades", assaultRifle) = 100;
    CreateContents(HG5B, clonk,1);
    return(1);
}
func CreateStalactites() {
	CreateObject(SL0D,1078,403 + 25);
	CreateObject(SL0D,1054,398 + 25);
	//CreateObject(SL0D,1013,440 + 25);
	CreateObject(SL0D,381,192 + 25);
	CreateObject(SL0D,410,190 + 25);
	CreateObject(SL0D,436,194 + 25);
	CreateObject(SL0D,459,190 + 25);
	CreateObject(SL0D,697,571 + 25);
	CreateObject(SL0D,618,593 + 25);
	CreateObject(SL0D,1595,190 + 25);
	CreateObject(SL0D,1640,169 + 25);
	CreateObject(SL0D,1573,400 + 25);
}
func CreateItemSpawns() {
  CreateObject(SPNP,1578,529);
  CreateObject(SPNP,1070,537);
  CreateObject(SPNP,711,224);
  CreateObject(SPNP,370,529);
  CreateObject(SPNP,1913,546);
  CreateObject(SPNP,663,688);
  CreateObject(SPNP,1110,638);
}

// spawn protection
global func FxSpawnTimer(pTarget, iEffectNumber,iEffectTime)
{
    EffectVar(3,pTarget,iEffectNumber)+=5;

  
    if(EffectVar(0,pTarget,iEffectNumber) <= 0)EffectVar(1,pTarget,iEffectNumber)=3;
    if(EffectVar(0,pTarget,iEffectNumber) >= 40)EffectVar(1,pTarget,iEffectNumber)=-3;
  
     
    if(Contained(pTarget))return(0);
    
    if(iEffectTime > 150) {
        SetClrModulation(RGB(255,255,255),pTarget);
        return(-1);
    }
    CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber),10),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber),10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
    CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber)-180,10),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber)-180,10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
    SetClrModulation(HSL(EffectVar(0,pTarget,iEffectNumber),255,128),pTarget);
  
    EffectVar(0,pTarget,iEffectNumber)+=EffectVar(1,pTarget,iEffectNumber);
    Extinguish(pTarget);
}

global func FxSpawnDamage(pTarget, iEffectNumber,foo,iCause)
{
    return(0);
}