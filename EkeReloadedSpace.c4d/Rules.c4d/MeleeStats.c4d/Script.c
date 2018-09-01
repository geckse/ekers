/*-- Hunger --*/

#strict 2

static aPlrState;
static aKills;
static aDeaths;
static aBulletShots;
static aBulletHits;
static aRecivedDamage;
static aDealedDamage;
static aPlrEvaluated;

global func InitPlayerData(iPlr){
 if(!aPlrState) aPlrState = [];
 if(!aKills) aKills = [];
 if(!aDeaths) aDeaths = [];
 if(!aBulletShots) aBulletShots = [];
 if(!aBulletHits) aBulletHits = [];
 if(!aRecivedDamage) aRecivedDamage = [];
 if(!aDealedDamage) aDealedDamage = [];
 if(!aPlrEvaluated) aPlrEvaluated = [];

 aKills[iPlr] = 0;
 aDeaths[iPlr] = 0;
 aBulletShots[iPlr] = 0;
 aBulletHits[iPlr] = 0;
 aRecivedDamage[iPlr] = 0;
 aDealedDamage[iPlr] = 0;
 aPlrEvaluated[iPlr] = false;

 aPlrState[iPlr] = true; // okay, wir sind da
 return(aPlrState[iPlr]);
 }
global func AddPlayerData(iPlr,type,val){
 if(!aPlrState) InitPlayerData(iPlr);
 if(!aPlrState[iPlr]) InitPlayerData(iPlr);

 var rule = FindObject(MEST);
 if(!rule) return;
 if(type == "BulletShots") aBulletShots[iPlr] += val;
 if(type == "BulletHits") aBulletHits[iPlr] += val;
 if(type == "Kills") aKills[iPlr] += val;
 if(type == "Deaths") aDeaths[iPlr] += val;
 if(type == "RecivedDamage") aRecivedDamage[iPlr] += val;
 if(type == "DealedDamage") aDealedDamage[iPlr] += val;
 return true;
 }

global func EvaDataPlr(iPlr){
   var retstring = "";
   aPlrEvaluated[iPlr] = true; // spieler nur einmal auswerten
   if(!FindObject(MEST)) return;

   retstring = Format("Kills:%d  Tode:%d  Trefferqoute:%d%",aKills[iPlr],aDeaths[iPlr],((100*aBulletHits[iPlr])/aBulletShots[iPlr]));

   return retstring;
}


protected func Activate(iByPlayer)
{
  var iPlr = iByPlayer;
  var data = Format("Tode: %d  Kills: %d|Schüsse: %d  Treffer: %d|Erhaltener Schaden: %d|Verursachter Schaden: %d|Treffer Qoute: %d%",aDeaths[iPlr],aKills[iPlr],aBulletShots[iPlr],aBulletHits[iPlr],aRecivedDamage[iPlr],aDealedDamage[iPlr],((100*aBulletHits[iPlr])/aBulletShots[iPlr]));
  MessageWindow(data, iByPlayer);
  return(1);
}