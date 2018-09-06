/*-- Neues Script --*/

#strict
#appendto SF5B

local iLastDamager;
local iFlightDistance;

public func IsClonk(){ return (true); }

public func & idDamage() { return Local(57); }

public func Damage(int iChange, int iByPlayer) {
  iLastDamager = iByPlayer;
  return _inherited(iChange, iByPlayer);
}

public func Initialize() {
  if(!GetEffect("DamageCounter", this())) AddEffect("DamageCounter", this(), 1, 0, 0, 0);
  iLastDamager = -1;
  return _inherited();
}

protected func Death(int iKilledBy) {
  if(iKilledBy == -1) iKilledBy = iLastDamager;
  CreateDeathLog(iKilledBy);
  AddPlayerData(iKilledBy,"Kills",1);
  AddPlayerData(GetOwner(),"Deaths",1);
  for(var i = 0; i < 12; i++){
      CreateParticle("EkeBlood", RandomX(-6,6), RandomX(-9,9), GetXDir(), GetYDir(), RandomX(80,140));
  }
  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this(), iKilledBy);
  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return 0;

  for(var pObj in FindObjects(Find_Container(this))) {
    Exit(pObj);
    SetXDir(GetXDir(this, 100), pObj, 100);
    SetYDir(GetYDir(this, 100), pObj, 100);
  }
  Sound("Die");
  DeathAnnounce();
  // Letztes Mannschaftsmitglied tot: Script benachrichtigen

    if(idDamage() == BLST) Zerfetz();
    //if(idDamage() != BLST) CreateBluter();
  if (!GetCrew(GetOwner()))
    GameCallEx("RelaunchPlayer", GetOwner(), GetKiller(), GetKiller());
  return 1;
}

public func Zerfetz(){
  // Effekte, Yay!
  Sound("Carnage");
  // Jetzt Körperteile verschleudern
  var dir = GetDir()*2-1;
  var angle, outspd;
  var head = CreateContents(CHED);
  SetDir(GetDir(), head); // Der Kopf zeigt sogar in die richtige Richtung
  Exit(head, 0, -6,, Sin(angle=Random(360), outspd=Random(7)), -Cos(angle, outspd), RandomX(-50, 50));
  Exit(CreateContents(CARM), dir*2, -2,, Sin(angle=Random(360), outspd=Random(7)), -Cos(angle, outspd), RandomX(-100, 100));
  Exit(CreateContents(CLEG), -dir*2, 2,, Sin(angle=Random(360), outspd=Random(7)), -Cos(angle, outspd), RandomX(-100, 100));
  Exit(CreateContents(CFLS),,,, Sin(angle=Random(360), outspd=Random(7)), -Cos(angle, outspd), RandomX(-100, 100));
  Exit(CreateContents(CARM), dir*2, -2,, Sin(angle=Random(360), outspd=Random(7)), -Cos(angle, outspd), RandomX(-100, 100));
  // Der Tote Clonk muss weg
  CreateSplatter(GetX(),GetY(),RandomX(8,20),RandomX(8,20),RandomX(10,30));
  CreateSplatter(GetX(),GetY(),RandomX(4,20),RandomX(4,10),RandomX(10,30));
  CastObjects(BLOP,RandomX(10,12),RandomX(10,12));

  for(var i = 0; i < 16; i++){
      CreateParticle("EkeBlood", RandomX(-16,16), RandomX(-16,16),0,0, RandomX(100,180));
  }

  return (RemoveObject());
}

protected func Destruction() {
  if(GetOwner() != -1) Kill();
}

protected func CreateDeathLog(int iKilledBy) {
  var iPlr = GetOwner(this);
  if(!GetPlayerName(iPlr))
    return 0;
  if(idDamage() == BU5B){
    idDamage() = BLIL;
  }

  if(iPlr != NO_OWNER)
  {
    if(iKilledBy != NO_OWNER && iKilledBy != iPlr)
      return(ShowMessage("$MsgItem1$", Format("<c %x>%s</c>", GetPlrColorDw(iKilledBy), FilterClanTag(GetPlayerName(iKilledBy))), idDamage(), Format("<c %x>%s</c>", GetPlrColorDw(iPlr), FilterClanTag(GetPlayerName(iPlr)))));
    if(iKilledBy == NO_OWNER || iKilledBy == iPlr)
      return(ShowMessage("$MsgSelf1$", Format("<c %x>%s</c>", GetPlrColorDw(iPlr), FilterClanTag(GetPlayerName(iPlr))), SKUL));
  }
  return(Log("! Test: iPlr: %v; iKilledBy: %v", iPlr, iKilledBy));
}
global func FxDamageCounterDamage (object pTarget, int iEffectNumber, int iDmgEngy, int iCause) {
  var idID = 0;
  if(iCause == 33) idID = BLST; // Explosion
  if(iCause == 35) idID = FLAM; // Feuer
  if(iCause == 37) idID = SUFO; // Ersticken
  if(iCause == 38) idID = ACID; // Säure
  if(idID) pTarget->~NewDamageID(idID);

  if(iDmgEngy < 0){
     AddPlayerData(LocalN("iLastDamager",pTarget),"DealedDamage",Abs(iDmgEngy/1000));
     AddPlayerData(pTarget->~GetOwner(),"RecivedDamage",Abs(iDmgEngy/1000));
  }
  return iDmgEngy;
}

public func QueryCatchBlow(pBy) {
  idDamage() = GetID(pBy);
  return _inherited(pBy);
}

public func NewDamageID(id idID, pObj) {
  idDamage() = idID;
}

global func Punch(object pObj, int iX) {
  if(this() && pObj) pObj->~NewDamageID(GetID(this()));
  return _inherited(pObj, iX);
}

global func DoEnergy(int iChange, object pObj) {
  if(this() && pObj) pObj->~NewDamageID(GetID(this()));
  return _inherited(iChange, pObj);
}

public func ControlThrow() {
  // Beim Werfen Besitzer setzen (für genauere Fragzuordnung)
  if(Contents()) SetOwner(GetOwner(), Contents());
  return _inherited();
}


//Für den T-Flint
protected func Collection(pObj) {
 var OldOwner=GetOwner(pObj);
 SetOwner(GetOwner(this()),pObj);
 if(GetID(pObj)==TFLN || GetID(pObj)==STFN) {
  //Log(Format("SetOwner(%d,Object(%d),GetName(Object(%d)))",OldOwner,ObjectNumber(pObj),ObjectNumber(pObj)));
  Schedule(Format("SetOwner(%d,Object(%d))",OldOwner,ObjectNumber(pObj)),1);
  }
 _inherited (...);
 }

protected func Collection2(pObj) {
 var OldOwner=GetOwner(pObj);
 SetOwner(GetOwner(this()),pObj);
 if(GetID(pObj)==TFLN || GetID(pObj)==STFN) {
  //Log(Format("SetOwner(%d,Object(%d),GetName(Object(%d)))",OldOwner,ObjectNumber(pObj),ObjectNumber(pObj)));
  Schedule(Format("SetOwner(%d,Object(%d))",OldOwner,ObjectNumber(pObj)),1);
  }
 _inherited (...);
 }