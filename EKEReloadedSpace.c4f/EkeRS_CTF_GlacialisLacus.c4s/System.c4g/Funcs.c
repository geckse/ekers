/*-- Funktionen --*/

#strict 2

static const SBRD_Relaunch = 0;

global func UpdateScoreboard(int iPlr)
{
  SetScoreboardData(iPlr,SBRD_Caption,GetTaggedPlayerName(iPlr));
  if(aRel[iPlr] >= 0){ SetScoreboardData(iPlr,SBRD_Relaunch,Format("%d",aRel[iPlr]));
  } else { SetScoreboardData(iPlr,SBRD_Relaunch,"<c aaaaaa><i>Out</i></c>"); }
  SetScoreboardData(SBRD_Caption,SBRD_Caption,"Scoreboard");
  SetScoreboardData(SBRD_Caption,SBRD_Relaunch,"{{VSFT}}");
  return true;
}

global func Fail() {return false;}