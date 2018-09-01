/*-- Neues Objekt --*/

#strict

local pClonk;
local iPlr;

local iMod;
local iTime;

local iRelaunchWait; // Wartezeit bis zum Relaunch
local iTapWait; // Wartezeit bis Tap spieler bei Posibeitritt

func Initialize() {
 iPlr= -1;
 iRelaunchWait = 210;
  return(1);
}

func Set(object clnk,  int plr, int mod, int tim) {

iPlr = plr;
pClonk = clnk;
iMod = mod;
if(tim) iTime = tim;
Enter(this(),clnk);
}


public func Check(){
if(GetOwner(pClonk) == -1) return(0);
if(iMod == 1) { iTime = 210; iMod++; }
if(iMod == 2) {
if(iTime > 0) iTime--;
var chgTime = MakeBetterTime(iTime);
PlayerMessage(iPlr,"$Wait$",this(),chgTime);
if(iTime < 1) iMod = 5;
 }
if(iMod == 5) {
   Exit(pClonk,-5,10);
   RemoveObject();
   CastParticles("PxSpark",RandomX(5,12),80,0,0,25,35,RGBa(255,255,255),RGBa(255,255,255));
}


}

public func MakeBetterTime(int Tim) {
var min = Tim /25 / 60;
var sek = Tim /25 % 60;
if(min) return(Format("%d : %d",min,sek));
if(!min) return(Format("%d",sek));
}