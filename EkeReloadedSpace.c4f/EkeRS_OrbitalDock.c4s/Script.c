/*-- Neues Szenario --*/

#strict

static aRel;

func Initialize() {
  aRel = [];
  CreateObject(ARWE);
  // Sternenhimmel
  SetSkyParallax(0, 50,50, 1,0);
  CreateObject(COFA);
  CreateObject(MEST);
  return(ScriptGo(1));
}

func Script2(){
    for(var spwn in FindObjects(Find_ID(SPNP))) {
    var Contents = [CA5B, OB5B, HG5B, GB5B, NH5B, GS5B, SG5B, RL5B, RB5B];
    CreateContents(Contents[Random(10)], spwn);
   }
}
func Script120(){
     goto(1);
}

func InitializePlayer(iPlr) {
  var clonk = GetCrew(iPlr);
  var assaultRifle = CreateContents(AR5B, clonk);
  LocalN("ammo", assaultRifle) = 100;
  LocalN("qGrenades", assaultRifle) = 100;
  CreateContents(HG5B, clonk,1);
  SetFoW (true, iPlr);
  aRel[iPlr] = 4;
  UpdateScoreboard(iPlr);
  }

func RelaunchPlayer(iPlr){

  if(aRel[iPlr] == 0){
  if(!aPlrEvaluated[iPlr]) AddEvaluationData(EvaDataPlr(iPlr),GetPlayerID(iPlr));
  UpdateScoreboard(iPlr);
   return false;
   }

     var wipf = PlaceAnimal(WIPF);
     var clonk = CreateObject(VSFT,GetX(wipf),GetY(wipf)-10,iPlr);
     MakeCrewMember(clonk,iPlr);
     SetCursor(iPlr,clonk);
     clonk->~DoEnergy(100);
     RemoveObject(wipf);
       var assaultRifle = CreateContents(AR5B, clonk);
        LocalN("ammo", assaultRifle) = 100;
        LocalN("qGrenades", assaultRifle) = 100;
        CreateContents(HG5B, clonk,1);
     aRel[iPlr]--;

  UpdateScoreboard(iPlr);
    return true;
}