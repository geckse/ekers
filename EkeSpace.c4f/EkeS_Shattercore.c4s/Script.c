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
      [666 + 350, 509 - 60],
      [469 + 350, 618 - 60],
      [1029 + 350, 829 - 60]
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
global func SpawnClonk(clonk)
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
  
    // equip clonk
    var assaultRifle = CreateContents(AR7A, clonk);
    assaultRifle->SetAmmoPercent(100);
    CreateContents(HG7A, clonk,1);
    return(1);
}

/*------------------------------------*\
    Item Spawns
\*------------------------------------*/
func CreateItemSpawns() {

    // spawning items
    itemSpawns = [CA7A, OB7A, GB7A, NH7A, SG7A, MS7A, HG7A, BB7A];
    itemSpawnsL = GetLength(itemSpawns);
    
    // spawn points
    CreateObject(IS7A,745 + 350,688 - 60);
    CreateObject(IS7A,588 + 350,1039 - 60);
    CreateObject(IS7A,509 + 350,299 - 60);

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
	// CreateObject(SL7A,1078,403 + 25);
    
}