 /*-- Asteriod Meele --*/

#strict

func Initialize() {
  // Sternenhimmel
  SetSkyParallax(0, 100,70, 1,0);
  CreateObject(COFA);  
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

/*------------------------------------*\
    Clonk Spawn/Respawn
\*------------------------------------*/
static clonkCategory;

private func InitializeClonk(clonk)
{ 
    // move new clonk to random respawn point, avoid spawning by hostiles
    var wipf = PlaceAnimal(WIPF);
    var spawnX = GetX(wipf);
    var spawnY = GetY(wipf);
    RemoveObject(wipf);
    
    for(var i = 1; i <= 4; i++) {
        var a2 = Find_Hostile(GetController(clonk));
        var a3 = Find_OCF(OCF_Alive);
        var a4 = Find_NoContainer();
        var a5 = Find_Distance(150, spawnX, spawnY);
        var hostile = FindObject2(a2, a3, a4, a5);
        if(hostile) {
            wipf = PlaceAnimal(WIPF);
            spawnX = GetX(wipf);
            spawnY = GetY(wipf);
            RemoveObject(wipf);
        }
    }
    SetPosition(spawnX, spawnY, clonk);

    // add spawn protection
    clonkCategory = GetCategory(clonk);
    AddEffect("Spawn",clonk,20,1);
  
    // equip clonk
    var assaultRifle = CreateContents(AR5B, clonk);
    LocalN("ammo", assaultRifle) = 100;
    LocalN("qGrenades", assaultRifle) = 100;
    CreateContents(HG5B, clonk,1);
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