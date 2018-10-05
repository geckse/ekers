/*--- Banner ---*/

#strict

local pTarget;

local iTeam;

static Banner_FlagX1, Banner_FlagX2, Banner_FlagY1, Banner_FlagY2;

public func SetFlagPositions(array positions){
	Banner_FlagX1 = positions[0][0];
	Banner_FlagY1 = positions[0][1];
	Banner_FlagX2 = positions[1][0];
	Banner_FlagY2 = positions[1][1];
}

public func GetFlagX(){
if(iTeam == 1) return(Banner_FlagX1);
if(iTeam == 2) return(Banner_FlagX2);
}
public func GetFlagY(){
if(iTeam == 1) return(Banner_FlagY1);
if(iTeam == 2) return(Banner_FlagY2);
}

global func GetTeamFlag(int iTam){
var flag = FindObject2(Find_ID(FL2G),Find_Func("GetFlagTeam",iTam));
 }

func GetFlagTeam(int iTam){
if(!iTam){ return(iTeam); }
else {
if(iTam == iTeam) return(1);
 }
}
func GetFlagTarget(){ return(pTarget); }

protected func Initialize()
{
  SetAction("Flya");
  Wind2Fly();
}
public func Set(object pTar){
pTarget = pTar;
SetAction("Fly",pTarget);

}
/* TimerCall */

private func Wind2Fly()
{

 if(GetY() > LandscapeHeight()-60){
    ClearTarget();
    SetPosition(GetFlagX(),GetFlagY());
 }

 if(pTarget){ // Getragen!
  var x = 7;
  if(GetDir(pTarget) == 1) x = -7;
  SetDir(BoundBy(7-(GetXDir(pTarget)/4), 0, 13));
  if(x == 7){ SetR(BoundBy(x-(GetXDir(pTarget)/2), -20, 20)); }
  if(x == -7){ SetR(BoundBy(x-(GetXDir(pTarget)/2), -20, 20)); }
 // Message("%d|%d",this(),BoundBy(7-(GetXDir(pTarget)/4), 0, 13),Sin (GetR(),-GetXDir(pTarget)));
  //SetR(BoundBy(Sin (GetR(),-GetXDir(pTarget)), -10, 10));
 if(!GetAlive(pTarget)){
  GameCallEx("OnFlagLost",this(),pTarget);
  ClearTarget();
  }
 }
 if(!pTarget) {
  SetDir(BoundBy(7 + GetWind() / 10, 0, 13));
  SetR(0);

  var pFlag = FindObject2(Find_ID(FL2G),Find_Distance(30),Find_Exclude(this()));
  if(pFlag){
   if(pFlag->~GetFlagTeam() != iTeam){
    if(Distance(GetX(),GetY(),GetFlagX(),GetFlagY()) < 40){
    GameCallEx("TakeOverFlag",pFlag,pFlag->~GetFlagTarget(),pFlag->~GetFlagTeam());
    }
   }
  }
  var pClonk = FindObject2(Find_Distance(30),Find_OCF(OCF_CrewMember()),Find_OCF(OCF_Alive()),Sort_Distance());
  if(GetPlayerTeam(GetOwner(pClonk)) == iTeam){
   if(Distance(GetX(),GetY(),GetFlagX(),GetFlagY()) > 10){
    Recover(pClonk);
    }
   }
  if(GetPlayerTeam(GetOwner(pClonk)) != iTeam){

    Capture(pClonk);

   }
  }

 }

public func Capture(pClonk){
if(!GetAlive(pClonk)) return(0);
Set(pClonk);
GameCallEx("OnFlagCapture",this(),pClonk);
}

public func Recover(pClonk){
if(!GetAlive(pClonk)) return(0);
ClearTarget();
//GameCallEx("OnFlagRecover",this(),pClonk);
SetPosition(GetFlagX(),GetFlagY());
}

public func ClearTarget(){
SetAction("Flya");
 if(pTarget){

  pTarget = 0;
  }
}

/* Farbe setzen */

public func Destruction(){
 SetPosition(GetFlagX(),GetFlagY());
}

protected func OnOwnerChanged()
{
  return(UpdateColor());
}

public func Unpacked()
{
  return(UpdateColor());
}

public func UpdateColor()
{
  // Farbmodulation nach Besitzer setzen
  SetClrModulation(GetTeamColor(iTeam));
  // Fertig
  return(1);
}

func Destruction(){

}