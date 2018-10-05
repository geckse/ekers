/*-- Neues Szenario --*/

#strict

static aRel;

func Initialize() {
  FL2G->SetFlagPositions([[112, 375], [2288, 375]]);
  aRel = [];
 capturelimit = 3;
  var flag1 = CreateObject(FL2G,112,375);
  LocalN("iTeam",flag1) = 1;
  var flag2 = CreateObject(FL2G,2288,375);
  LocalN("iTeam",flag2) = 2;
  CreateObject(NF7A);
  CreateObject(SW7A);
  CreateObject(AM7A);
  var pFlag1 = FindObject2(Find_ID(FL2G),Find_Func("GetFlagTeam",1));
  pFlag1->~UpdateColor();
  var pFlag2 = FindObject2(Find_ID(FL2G),Find_Func("GetFlagTeam",2));
  pFlag2->~UpdateColor();
  // Sternenhimmel
  CreateObject(CF7A);
  return(ScriptGo(1));
}

func GetTeamStartPosition(iTeam, fY)
{
  if(iTeam==1) { if(!Random(2)){
     if(!fY) return(95);
     return(275);
    } else {
     if(!fY) return(90);
     return(375);
      }
    }
  if(iTeam==2) { if(!Random(2)){
     if(!fY) return(2305);
     return(275);
    } else {
     if(!fY) return(2310);
     return(375);
      }
    }
}

func Script2(){
    for(var spwn in FindObjects(Find_ID(IS7A))) {
    var Contents = [CA7A, OB7A, HG7A, GB7A, NH7A, GS7A, SG7A];
    CreateContents(Contents[Random(GetLength(Contents))], spwn);
   }
}
func Script120(){
     goto(1);
}

func InitializePlayer(iPlr) {
  var clonk = GetCrew(iPlr);
  if(!Random(2)){
         var assaultRifle = CreateContents(AR7A, clonk);
         assaultRifle->SetAmmoPercent(100);
         CreateContents(HG7A, clonk,2);
  } else {
         var sRifle = CreateContents(SG7A, clonk);
         sRifle->SetAmmoPercent(100);
         CreateContents(CA7A, clonk,1);
         CreateContents(HG7A, clonk,2);
  }

  SetPosition(GetTeamStartPosition(GetPlayerTeam(iPlr)),GetTeamStartPosition(GetPlayerTeam(iPlr),true),clonk);
  aRel[iPlr] = 4;
  //UpdateScoreboard(iPlr);
  }

func RelaunchPlayer(iPlr){

  if(aRel[iPlr] == 0){

  //UpdateScoreboard(iPlr);
   return false;
   }

     var spawn = CreateObject(QRE1,GetTeamStartPosition(GetPlayerTeam(iPlr)),GetTeamStartPosition(GetPlayerTeam(iPlr),true),iPlr);
     var clonk = CreateObject(SF7A,20,20,iPlr);
     MakeCrewMember(clonk,iPlr);
     SetCursor(iPlr,clonk);
     clonk->~DoEnergy(100);
     spawn->~Set(clonk,iPlr,1);
     Enter(spawn,clonk);
  if(!Random(2)){
         var assaultRifle = CreateContents(AR7A, clonk);
         LocalN("ammo", assaultRifle) = 100;
         LocalN("qGrenades", assaultRifle) = 100;
         CreateContents(HG7A, clonk,2);
  } else {
         var sRifle = CreateContents(SG7A, clonk);
         LocalN("ammo", sRifle) = 100;
         CreateContents(CA7A, clonk,1);
         CreateContents(HG7A, clonk,2);
  }

     aRel[iPlr]++;

  //UpdateScoreboard(iPlr);
    return true;
}

static scoreleft, scoreright;
static killleft, killright;
static capturelimit;
static stateleft, stateright;

func OnFlagLost(object Flagg, object pClonk){
Log("%s(%s) hat die eigene gegnerische Flagge fallen lassen!",GetTeamName(GetPlayerTeam(GetOwner(pClonk))),GetTaggedPlayerName(GetOwner(pClonk)));
 return(1);
}

func OnFlagCollect(object Flagg, object pClonk){
Log("%s(%s) hat die eigene Flagge wieder!",GetTeamName(GetPlayerTeam(GetOwner(pClonk))),GetTaggedPlayerName(GetOwner(pClonk)));
 return(1);
}

func OnFlagCapture(object Flagg, object pClonk){
Log("%s(%s) hat die Flagge von %s!",GetTeamName(GetPlayerTeam(GetOwner(pClonk))),GetTaggedPlayerName(GetOwner(pClonk)),GetTeamName(Flagg->~GetFlagTeam()));
 return(1);
}

func TakeOverFlag(object pFlag, object pClonk,int iTeam){
var iscore;
var stTeam1,stTeam2;

if(iTeam == 2){
Score(1);
stTeam1 = GetTeamName(1);
stTeam2 = GetTeamName(2);
iscore = scoreleft;
}
if(iTeam == 1){
Score(2);
stTeam1 = GetTeamName(2);
stTeam2 = GetTeamName(1);
iscore = scoreright;
}

pFlag->~ClearTarget();
Exit(pFlag);
SetPosition(pFlag->~GetFlagX(),pFlag->~GetFlagY(),pFlag);
Sound("Ding",1);

Log("%s(%s) hat die Flagge von %s erfolgreich geklaut! Und hat damit nun %d Punkte.",stTeam1,GetTaggedPlayerName(GetOwner(pClonk)),stTeam2,iscore);

}

// Flagge wird abgeliefert
global func Score(iTeam)
{
  if(iTeam==1)
  {
    DoWealth(GetPlrByTeam(1), 50);
    Sound("Cash");
    if(++scoreleft>=capturelimit) Team2Lose();

  }
  if(iTeam==2)
  {
    DoWealth(GetPlrByTeam(2), 50);
    Sound("Cash");
    if(++scoreright>=capturelimit) Team1Lose();
  }
  //ActualizeScoreboard();
}

global func Team1Lose()
{
  Log("$MsgRedWin$");
  var winnerTeam = 2;
// ...und die Verlierer eliminieren
  for (var i = GetPlayerCount(); i--;)
   {
  if (CheckTeam(GetPlayerByIndex(i)) != winnerTeam)
  EliminatePlayer(GetPlayerByIndex(i));
   }
}

global func Team2Lose()
{
  Log("$MsgBlueWin$");
  var winnerTeam = 1;
// ...und die Verlierer eliminieren
  for (var i = GetPlayerCount(); i--;)
   {
  if (CheckTeam(GetPlayerByIndex(i)) != winnerTeam)
  EliminatePlayer(GetPlayerByIndex(i));
   }
}




global func GetPlrByTeam(iTeam, iIndex)
{
  var iCount;
  for (var i = GetPlayerCount(); i--;)
  {
    if (CheckTeam(GetPlayerByIndex(i)) == iTeam)
      Var(iCount++) = i;
  }
  if(!iCount) return -1;
  return Var(iIndex % iCount);
}

global func GetTeamCount(iTeam)
{
  var iCount;
  for (var i = GetPlayerCount(); i--;)
  {
    if (CheckTeam(GetPlayerByIndex(i)) == iTeam)
      iCount++;
  }
  return iCount;
}

global func CheckTeam(int iPlr)
{
  return GetPlayerTeam(iPlr);
}