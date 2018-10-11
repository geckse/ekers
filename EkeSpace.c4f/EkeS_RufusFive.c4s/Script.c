 /*-- Rufus V --*/

#strict 2

static clonkSpawns;
static clonkSpawnsL;
static clonkCategory;

static itemSpawns;
static itemSpawnsL;

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

    CreateObject(CF7A);
    CreateEnvironment();
    CreateItemSpawns();

    return(ScriptGo(1));
}
func Script1()
{
  SetMaxPlayer();
  return(1);
}

func Script2(){
    
    // create items in spawn points
    for(var spwn in FindObjects(Find_ID(IS7A))) {
        
        var r = Random(itemSpawnsL);
        
        // half chance for specific items
        if (itemSpawns[r] == SG7A || itemSpawns[r] == NH7A) {
            r = Random(itemSpawnsL);
        }
        CreateContents(itemSpawns[r], spwn);
   }
}
func Script120(){
     goto(2);
}

/*------------------------------------*\
    Clonk Spawn/Respawn
\*------------------------------------*/
func InitializeClonk(clonk)
{
    
    // move new clonk to random respawn point, avoid spawning by hostiles
    var r = Random(clonkSpawnsL);
    for(var i = 1; i <= 4; i++) {
        var a2 = Find_Hostile(GetController(clonk));
        var a3 = Find_OCF(OCF_Alive);
        var a4 = Find_NoContainer();
        var a5 = Find_Distance(150, clonkSpawns[r][0], clonkSpawns[r][1]);
        var hostile = FindObject2(a2, a3, a4, a5);
        if(hostile) {
            r = Random(clonkSpawnsL);
        }
    }
    SetPosition(clonkSpawns[r][0], clonkSpawns[r][1], clonk);

    // add spawn protection
    clonkCategory = GetCategory(clonk);
    AddEffect("Spawn",clonk,20,1);
  
    // equip clonk
    var assaultRifle = CreateContents(AR7A, clonk);
    assaultRifle->SetAmmoPercent(100);
    CreateContents(HG7A, clonk,1);
    return(1);
}
// spawn protection
global func FxSpawnTimer(pTarget, iEffectNumber,iEffectTime) {
    EffectVar(3,pTarget,iEffectNumber)+=5;

  
    if(EffectVar(0,pTarget,iEffectNumber) <= 0)EffectVar(1,pTarget,iEffectNumber)=3;
    if(EffectVar(0,pTarget,iEffectNumber) >= 40)EffectVar(1,pTarget,iEffectNumber)=-3;
  
     
    if(Contained(pTarget))return(0);
    
    if(iEffectTime > 150) {
        SetClrModulation(RGB(255,255,255),pTarget);
        SetCategory(clonkCategory,pTarget);
        return(-1);
    }
    CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber),10),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber),10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
    CreateParticle("PSpark",GetX(pTarget)+Cos(EffectVar(3,pTarget,iEffectNumber)-180,10),GetY(pTarget)+Sin(EffectVar(3,pTarget,iEffectNumber)-180,10),0,0,30,HSL(EffectVar(0,pTarget,iEffectNumber),255,128));
    SetClrModulation(HSL(EffectVar(0,pTarget,iEffectNumber),255,128),pTarget);
  
    EffectVar(0,pTarget,iEffectNumber)+=EffectVar(1,pTarget,iEffectNumber);
    Extinguish(pTarget);
    SetCategory(C4D_Vehicle,pTarget);
}

global func FxSpawnDamage(pTarget, iEffectNumber,foo,iCause) {
    return(0);
}

/*------------------------------------*\
    Item Spawns
\*------------------------------------*/
func CreateItemSpawns() {

    // spawning items
    itemSpawns = [CA7A, OB7A, GB7A, NH7A, SG7A, MS7A, HG7A, BB7A];
    itemSpawnsL = GetLength(itemSpawns);
    
    // spawn points
    CreateObject(IS7A,1578,529);
    CreateObject(IS7A,1070,537);
    CreateObject(IS7A,711,224);
    CreateObject(IS7A,370,529);
    CreateObject(IS7A,1913,546);
    CreateObject(IS7A,663,688);
    CreateObject(IS7A,1110,638);

}

/*------------------------------------*\
    Environment
\*------------------------------------*/
func CreateEnvironment() {
    
    // Sky
    SetSkyParallax (0,17,19,0,0,0,0);

    // Fog
    for(var i=0;i<90;++i)
    CreateParticle("Fog",Random(LandscapeWidth()),Random(LandscapeHeight()),0,0,RandomX(900,1700));

    // stalactites
	CreateObject(SL7A,1078,403 + 25);
	CreateObject(SL7A,1054,398 + 25);
	CreateObject(SL7A,381,192 + 25);
	CreateObject(SL7A,436,194 + 25);
	CreateObject(SL7A,459,190 + 25);
	CreateObject(SL7A,697,571 + 25);
	CreateObject(SL7A,618,593 + 25);
	CreateObject(SL7A,1595,190 + 25);
	CreateObject(SL7A,1640,169 + 25);
	CreateObject(SL7A,1573,400 + 25);
    
}