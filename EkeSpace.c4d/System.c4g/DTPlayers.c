/*-- Helper functions for iterating through all players and teams --*/
#strict 2

static const Player_Number = 0;
static const Player_ID = 1;
static const Player_Name = 2;
static const Player_TaggedName = 3;
static const Player_Color = 4;
static const Player_Team = 5;
static const Player_Type = 6;

global func GetPlayers(int team, bool exclude)
{
	var ret = [];
	for(var plr, plrTeam, i = 0; (i < GetPlayerCount()) && ((plrTeam = GetPlayerTeam(plr = GetPlayerByIndex(i))) || true); ++i)
	{
		if(!team || (team == plrTeam) != exclude)
		{
			var plrInfo = [];
			plrInfo[Player_Number] = plr;
			plrInfo[Player_ID] = GetPlayerID(plr);
			plrInfo[Player_Name] = GetPlayerName(plr);
			plrInfo[Player_TaggedName] = GetTaggedPlayerName(plr);
			plrInfo[Player_Color] = GetPlrColorDw(plr);
			plrInfo[Player_Team] = GetPlayerTeam(plr);
			plrInfo[Player_Type] = GetPlayerType(plr);
			ret[GetLength(ret)] = plrInfo;
		}
	}
	
	return ret;
}

global func GetPlayerNumbers(int team, bool exclude)
{
	var ret = [];
	for(var plr, i = 0; (i < GetPlayerCount()) && ((plr = GetPlayerByIndex(i)) || true); ++i)
	{
		if(!team || (team == GetPlayerTeam(plr)) != exclude)
		{
			ret[GetLength(ret)] = plr;
		}
	}
	return ret;
}

global func GetTaggedTeamName(int team)
{
	return Format("<c %x>%s</c>", GetTeamColor(team), GetTeamName(team));
}

static const Team_ID = 0;
static const Team_Name = 1;
static const Team_TaggedName = 2;
static const Team_Color = 3;
static const Team_Players = 4;

global func GetTeams()
{
	var ret = [];
	for(var team, i = 0; (i < GetTeamCount()) && ((team = GetTeamByIndex(i)) || true); ++i)
	{
		var teamInfo = [];
		teamInfo[Team_ID] = team;
		teamInfo[Team_Name] = GetTeamName(team);
		teamInfo[Team_TaggedName] = GetTaggedTeamName();
		teamInfo[Team_Color] = GetTeamColor(team);
		teamInfo[Team_Players] = GetPlayers(team);
		ret[GetLength(ret)] = teamInfo;
	}
	return ret;
}

global func GetTeamIDs()
{
	var ret = [];
	for(var team, i = 0; (i < GetTeamCount()) && ((team = GetTeamByIndex(i)) || true); ++i)
	{
		ret[GetLength(ret)] = team;;
	}
	return ret;
}