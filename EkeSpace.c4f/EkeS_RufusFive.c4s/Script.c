 /*-- Rufus V --*/

#strict 2

static clonkSpawns;
static clonkSpawnsL;
static clonkSpawnsR;

static itemSpawns;
static itemSpawnsL;
static itemSpawnsR;

func Initialize() {

    // declare clonk respawn points
    clonkSpawns = [
      [1058, 0299],
      [1380, 0438],
      [0580, 0499]
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

        while(r == itemSpawnsR || !r) var r = Random(itemSpawnsL);

        if(itemSpawns[r] == NH7A || itemSpawns[r] == SG7A) {
            if(!Random(2)) {
                r = Random(itemSpawnsL);
            }
        }

        CreateContents(itemSpawns[r], spwn);

        itemSpawnsR = r;
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
    while(r == clonkSpawnsR) {
        r = Random(clonkSpawnsL);
    }
    SetPosition(clonkSpawns[r][0], clonkSpawns[r][1], clonk);
    clonkSpawnsR = r;
  
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

    // declare spawning items
    itemSpawns = [CA7A, OB7A, HG7A, NH7A, SG7A, PM7A];
    itemSpawnsL = GetLength(itemSpawns);
    
    // spawn points
    CreateObject(IS7A,1578,529);
    CreateObject(IS7A,663,688);
    CreateObject(IS7A,1110,647);

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
	CreateObject(SL7A,697,571 + 25);
	CreateObject(SL7A,618,593 + 25);
	CreateObject(SL7A,1573,400 + 25);
    
}