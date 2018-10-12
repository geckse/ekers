#strict 2
#appendto SF7A

local clonkName;
local clonkRank;

func GetRankName()
{
  return $ClonkRanks$[GetRank()];
}

func Recruitment()
{
  clonkName = Format("%s", GetName());
  SetName("");
  clonkRank = GetRank();
  AddEffect("RankCheck", this, 1, 1, this);
  return _inherited(...);
}

func UpdateNameAndRankMessage()
{
  var xOffset = -5;
  if(!GetPortrait())
  {
    xOffset -= 46; // 4 * C4SymbolSize / 3
  }
  CustomMessage(Format("@%s|%s", GetRankName(), clonkName), 0, GetOwner(), xOffset, 55, 0, 0, "1", 1);
}

func CrewSelection(deselect)
{
  if(!deselect && GetCursor(GetOwner()) == this)
  {
    UpdateNameAndRankMessage();
  }
  return _inherited(deselect, ...);
}

func Death()
{
  SetName(clonkName);
  return _inherited(...);
}

func FxRankCheckTimer()
{
  var currentRank = GetRank();
  if(currentRank != clonkRank)
  {
    var owner = GetOwner();
    if(owner != NO_OWNER)
    {
      clonkRank = currentRank;
      if(GetCursor(owner) == this)
      {
        UpdateNameAndRankMessage();
      }

      Message("$RankUp$", this, clonkName, GetRankName());
    }
  }
}
