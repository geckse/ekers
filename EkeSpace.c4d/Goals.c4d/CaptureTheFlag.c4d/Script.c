/* Capture the Flag */

#strict 2
#include MELE

static goal_ctf;

local score;
local targetScore;
local flagPositions;

static const SBRD_CTF_Goal = 2147483647;

func Initialize()
{
  // Zielpunktzahl = Platzierungsanzahl
  if(goal_ctf)
  {
    goal_ctf->IncreaseTargetScore();
    return RemoveObject();
  }

  targetScore = 1;
  goal_ctf = this;

  score = [];
  flagPositions = [];

  SetScoreboardData(SBRD_Caption, SBRD_Caption, GetName());
  SetScoreboardData(SBRD_CTF_Goal, SBRD_Caption, "$GoalPoints$");

  SetScoreboardData(SBRD_Caption, 0, "{{FL2G}}");


  UpdateScoreboardGoal();

  for(var team in GetTeamIDs())
  {
    SetScoreboardData(team, SBRD_Caption, GetTaggedTeamName(team));
    UpdateScoreboard(team);
  }

  return _inherited(...);
}

// array of [x,y], indexed by team IDs

func SetFlagPositions(array positions)
{
  flagPositions = positions;

  for(var team in GetTeamIDs())
  {
    SpawnFlag(team);
  }
}

func SpawnFlag(int team)
{
  var position = flagPositions[team];

  var flag = FL2G->CreateObject(FL2G, position[0], position[1], NO_OWNER);
  flag->SetTeam(team);

  AddEffect("Flag", flag, 1, 0, this);
}

func FxFlagStop(object target, int effectNumber, int reason, bool temp)
{
  if(!temp)
  {
    SpawnFlag(target->GetFlagTeam());
  }
}

func IncreaseTargetScore()
{
  ++targetScore;
  UpdateScoreboardGoal();
}

func SetTargetScore(int score)
{
  targetScore = score;
  UpdateScoreboardGoal();
}

func UpdateScoreboardGoal()
{
  SetScoreboardData(SBRD_CTF_Goal, 0, Format("$Points$", targetScore), -1);
}

func UpdateScoreboard(int team)
{
  var teamScore = score[team];
  SetScoreboardData(team, 0, Format("%d", teamScore), teamScore);
  SortScoreboard(0, true);
}


func InitializePlayer(int plr)
{
  DoScoreboardShow(1, plr + 1);

  return inherited(plr, ...);
}

func Activate(int plr)
{
  var pointsLeft = targetScore - score[GetPlayerTeam(plr)];

  MessageWindow(Format(["$InfoSingular$", "$InfoPlural$"][pointsLeft != 1], pointsLeft), plr);
}

func IncreaseScore(int team)
{
  var teamScore = ++score[team];
  UpdateScoreboard(team);

  if(teamScore >= targetScore)
  {
    Log("$TeamWon$", GetTaggedTeamName(team));
    for(var plr in GetPlayerNumbers(team, true))
    {
      EliminatePlayer(plr);
    }
  }
}

func OnFlagLost(object flag, object clonk)
{
  var capturePlr = GetOwner(clonk);
  var captureTeam = GetPlayerTeam(capturePlr);

  Log("$FlagLostBy$", GetTaggedPlayerName(capturePlr), GetTaggedTeamName(captureTeam));
}

func OnFlagCapture(object flag, object clonk)
{
  var capturePlr = GetOwner(clonk);
  var captureTeam = GetPlayerTeam(capturePlr);
  var flagTeam = flag->GetFlagTeam();

  Log("$FlagTakenBy$", GetTaggedPlayerName(capturePlr), GetTaggedTeamName(captureTeam), GetTaggedTeamName(flagTeam));
}

func OnFlagRecover(object flag, object clonk)
{
  var position = flagPositions[flag->GetFlagTeam()];
  flag->SetPosition(position[0], position[1]);

  var capturePlr = GetOwner(clonk);
  var captureTeam = GetPlayerTeam(capturePlr);

  Log("$FlagRecoveredBy$", GetTaggedPlayerName(capturePlr), GetTaggedTeamName(captureTeam));
}

func TakeOverFlag(object flag, object clonk, int flagTeam)
{
  var capturePlr = GetOwner(clonk);
  var captureTeam = GetPlayerTeam(capturePlr);

  flag->ClearTarget();
  var position = flagPositions[flagTeam];
  flag->SetPosition(position[0], position[1]);

  Sound("Ding", true);
  Log("$FlagCapturedBy$", GetTaggedPlayerName(capturePlr), GetTaggedTeamName(captureTeam), GetTaggedTeamName(flagTeam), score[captureTeam] + 1);

  IncreaseScore(captureTeam);
}