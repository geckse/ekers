/* Equiem */

#strict

static uziBird;
static itemSpawns;
static itemSpawnsL;

func GetSftSuit() { return("Urban"); }

func Initialize()
{
  CreateUziBird();

  // create item spawns
  itemSpawns = [NH7A, PM7A];
  itemSpawnsL = GetLength(itemSpawns);
  CreateObject(IS7A,500,395);

  // set sky color
  // SetSkyAdjust(RGBa(220,220,255,50), RGB(0,0,0));

  CreateEnvironment();

  ScriptGo(1);
  return(1);
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
        if (itemSpawns[r] == NH7A) {
            r = Random(itemSpawnsL);
        }
        CreateContents(itemSpawns[r], spwn);
   }
}

func Script15()
{
  // es sollen genug Miffel im Graben #2 leben
  var zapCount = ObjectCount(MI5B);
  if (zapCount < 3) CreateObject(MI5B, RandomX(170, 220), RandomX(200, 400), NO_OWNER);

  // es sollen genug Stippel im Graben #5 leben
  var zapCount = ObjectCount(ST5B);
  if (zapCount < 7) CreateObject(ST5B, RandomX(770, 840), 400, NO_OWNER);

  // es sollen genug Feuermonster im Graben #4 leben
  var zapCount = ObjectCount(FMNS);
  if (zapCount < 2) CreateObject(FMNS, RandomX(645, 690), 400, NO_OWNER);

  // ist unser UziBird noch am Leben?
  if (!GetAlive(uziBird)) CreateUziBird();

  goto(2);
  return(1);
}

private func CreateUziBird()
{
  uziBird = CreateObject(BIRD, Random(LandscapeWidth()), 25, NO_OWNER);
  var uzi = CreateContents(SG7A, uziBird);
  uzi->SetAmmoPercent(100);
  return(1);
}

func InitializeClonk(clonk)
{
  SetPosition(Random(LandscapeWidth()), Random(100) + 25, clonk);

  // equip clonk
  CreateContents(PM7A, clonk);

  // pull pistol
  clonk -> Holster();

  // make ready for jetpack
  clonk -> SetAction("Jump");
  // set jetpack active
  clonk -> Start(COMD_Up);
  clonk -> LocalN("slow") = true;

  return(1);
}



/*------------------------------------*\
    Environment
\*------------------------------------*/
func CreateEnvironment() {

    // Sky
    SetSkyParallax (0,17,19,0,0,0,0);
    SetGamma(RGB(15,15,15),RGB(118,118,118),RGB(215,215,215));

    // Fog
    for(var i=0;i<20;++i)
    CreateParticle("Fog",Random(LandscapeWidth()),Random(LandscapeHeight()),0,0,RandomX(900,1700));

}