/*--- Banner ---*/

#strict 2

local pTarget;

local team;
local stolen;

func SetTeam(int newTeam)
{
	team = newTeam;
	UpdateColor();
}

func GetFlagTeam()
{
  return team;
}

func GetFlagTarget() { return pTarget; }

protected func Initialize()
{
  SetAction("Flya");
  Wind2Fly();
}

public func Set(object pTar){
  pTarget = pTar;
  SetAction("Fly", pTarget);
}

/* TimerCall */
private func Wind2Fly()
{
  if(pTarget) // Getragen
  {
    var x = 7;
    if(GetDir(pTarget) == 1) x = -7;
    SetDir(BoundBy(7-(GetXDir(pTarget)/4), 0, 13));
    if(x == 7){ SetR(BoundBy(x-(GetXDir(pTarget)/2), -20, 20)); }
    if(x == -7){ SetR(BoundBy(x-(GetXDir(pTarget)/2), -20, 20)); }

    if(!GetAlive(pTarget))
    {
      GameCallEx("OnFlagLost",this(),pTarget);
      ClearTarget();
    }
  }
  else
  {
    SetDir(BoundBy(7 + GetWind() / 10, 0, 13));
    SetR(0);

    if(!stolen)
    {
      var pFlag = FindObject2(Find_ID(FL2G),Find_Distance(30),Find_Exclude(this));
      if(pFlag && pFlag->~GetFlagTeam() != team)
      {
        GameCallEx("TakeOverFlag",pFlag,pFlag->~GetFlagTarget(),pFlag->~GetFlagTeam());
        pFlag->LocalN("stolen") = false;
      }
    }

    var pClonk = FindObject2(Find_Distance(30),Find_OCF(OCF_CrewMember),Find_OCF(OCF_Alive),Sort_Distance());
    if(stolen)
    {
      if(GetPlayerTeam(GetOwner(pClonk)) == team)
      {
        Recover(pClonk);
      }
    }

    if(GetPlayerTeam(GetOwner(pClonk)) != team)
    {
      Capture(pClonk);
    }
  }
}

public func Capture(pClonk){
  if(!GetAlive(pClonk)) return(0);
  Set(pClonk);
  GameCallEx("OnFlagCapture",this(),pClonk);
  stolen = true;
}

public func Recover(pClonk)
{
  if(!GetAlive(pClonk)) return(0);
  ClearTarget();
  GameCallEx("OnFlagRecover",this(),pClonk);
  stolen = false;
}

public func ClearTarget()
{
  SetAction("Flya");
  pTarget = 0;
}

protected func OnOwnerChanged()
{
  return UpdateColor();
}

public func UpdateColor()
{
  // Farbmodulation nach Besitzer setzen
  SetClrModulation(GetTeamColor(team));
}
