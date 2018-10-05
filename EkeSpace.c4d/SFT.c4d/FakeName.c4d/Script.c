#strict 2

local clonkName;

func Recruitment()
{
  clonkName = Format("%s", GetName());
  SetName("");
  return _inherited(...);
}
func CrewSelection(deselect)
{
    if(!deselect) {
        CustomMessage(Format("@%s|%s", $ClonkRanks$[GetRank(this())] ,clonkName), 0, GetOwner(), -5,55, 0, 0, "1", 1);
    }
    return _inherited(...);
}
func DeathAnnounce ()
{
    Message("%s $DeathMsg$", this(), clonkName);
    return(1);
}