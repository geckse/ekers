/* Deathmatch */

#strict
#include MELE

static deathmatchRule;

local relaunchs;
local kills;
local selfkills;
local maxRelaunchs;

protected func Initialize()
{
    deathmatchRule = 1;

    relaunchs = CreateArray();
    kills = CreateArray();
    selfkills = CreateArray();

    // Relaunchanzahl = Platzierungsanzahl
    var goal;
    if (goal = FindObject(GetID()))
    {
        LocalN("maxRelaunchs", goal) += 1;
        return(RemoveObject());
    }
    maxRelaunchs = 1;

    return _inherited(...);
}


func InitializePlayer(player, x, y, base, team)
{
    if(GetPlayerType(player) == C4PT_Script) return(0);
    var playerID = GetPlayerID(player);

    SetScoreboardData(SBRD_Caption, SBRD_Caption, "Score", SBRD_Caption);

    SetScoreboardData(SBRD_Caption, 1, "{{SF7A}}", 1);
    SetScoreboardData(SBRD_Caption, 2, "{{AR7A}}", 2);
    SetScoreboardData(SBRD_Caption, 3, "{{HG7A}}", 3);
    SetScoreboardData(playerID, SBRD_Caption, GetTaggedPlayerName(player), playerID);
    SetScoreboardData(playerID, 1, Format("%d", maxRelaunchs), 10);
    SetScoreboardData(playerID, 2, "0", 0);
    SetScoreboardData(playerID, 3, "0", 0);
    SortScoreboard(1, true);

    DoScoreboardShow(1, player + 1);

    GameCall("InitializeClonk", GetCrew(player));
    return(inherited(player, x, y, base, team));   
}

func Activate(player)
{
    var playerID = GetPlayerID(player);

    var r = maxRelaunchs - relaunchs[playerID];
    var k = kills[playerID];
    var s = selfkills[playerID];

    MessageWindow(Format("$Info$", r, k, s), player);
}

func RelaunchPlayer(player)
{
    if(GetPlayerType(player) == C4PT_Script) return(0);
    var playerID = GetPlayerID(player);

    relaunchs[playerID]++;

    var rest = maxRelaunchs - relaunchs[playerID];

    if (rest < 0) {
        SetScoreboardData(playerID, 1, "-", rest);
    }
    else {
        SetScoreboardData(playerID, 1, Format("%d", rest), rest);
    }

    SetScoreboardData(playerID, 2, Format("%d", kills[playerID]), kills[playerID]);
    SortScoreboard(1, true);

    if (rest < 0) return;

    var clonk = CreateObject(SF7A, 0, 0, player);
    MakeCrewMember(clonk, player);
    clonk -> DoEnergy(100);
    SelectCrew(player, clonk, 1);

    GameCall("InitializeClonk", clonk);
    return(1);
}

func ReportHomicide(killer, victim)
{
    if(GetPlayerType(killer) == C4PT_Script) return(0);
    if(GetPlayerType(victim) == C4PT_Script) return(0);
    var killerID = GetPlayerID(killer);
    if (!killerID) return;

    if (killer == victim)
    {
        selfkills[killerID]++;
        SetScoreboardData(killerID, 3, Format("%d", selfkills[killerID]), selfkills[killerID]);
    }
    else
    {
        kills[killerID]++;
        var rest = maxRelaunchs - relaunchs[killerID];

        SetScoreboardData(killerID, 1, Format("%d", rest), rest);
        SetScoreboardData(killerID, 2, Format("%d", kills[killerID]), kills[killerID]);
        SortScoreboard(1, true);
    }
}

protected func RemovePlayer(player)
{
    if(GetPlayerType(player) == C4PT_Script) return(0);
    var playerID = GetPlayerID(player);

    SetScoreboardData(playerID, SBRD_Caption, GetPlayerName(player));
    SetScoreboardData(playerID, 1, "-");
}