#strict 2

local clonkName;
local clonkRank;

func Recruitment()
{
  clonkName = Format("%s", GetName());
  SetName("");
  clonkRank = GetRank(this);
  AddEffect("RankCheck", this, 1, 1, this);
  return _inherited(...);
}
func CrewSelection(deselect)
{
    if(!deselect) {
        CustomMessage(Format("@%s|%s", $ClonkRanks$[GetRank(this())] ,clonkName), 0, GetOwner(), -5,55, 0, 0, "1", 1);
    }
    return _inherited(deselect, ...);
}

func Death()
{
  SetName(clonkName);
  return _inherited(...);
}

global func GetName(object target, id id)
{
    if(id)
    {
        return inherited(target, id, ...);
    }

    return LocalN("clonkName", target || this) || inherited(target, ...);
}

func FxRankCheckTimer()
{
  var currentRank = GetRank(this);
  if (currentRank != clonkRank)
  {
    var owner = GetOwner(this);
    if(owner != NO_OWNER)
    {
      clonkRank = currentRank;
      if(GetCursor(owner) == this) CustomMessage(Format("@%s|%s", $ClonkRanks$[clonkRank], clonkName), 0, owner, -5,55, 0, 0, "1", 1);
      var RankUpMsg = Format("$RankUp$", clonkName, $ClonkRanks$[clonkRank]);
      PlayerMessage(owner, RankUpMsg, this);
    }
  }
}