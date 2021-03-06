/*-- Neues Szenario --*/

#strict 2

func Initialize() {
  // team IDs starten bei 1
  goal_ctf->SetFlagPositions([0, [112, 375], [2288, 375]]);
  return(ScriptGo(1));
}

func GetTeamStartPosition(iTeam, fY)
{
  if(iTeam==1) { if(!Random(2)){
     if(!fY) return(95);
     return(275);
    } else {
     if(!fY) return(90);
     return(375);
      }
    }
  if(iTeam==2) { if(!Random(2)){
     if(!fY) return(2305);
     return(275);
    } else {
     if(!fY) return(2310);
     return(375);
      }
    }
}

func Script2(){
    for(var spwn in FindObjects(Find_ID(IS7A))) {
    var Contents = [CA7A, OB7A, HG7A, GB7A, NH7A, GS7A, SG7A];
    CreateContents(Contents[Random(GetLength(Contents))], spwn);
   }
}
func Script120(){
     goto(1);
}

func InitializePlayer(iPlr) {
  var clonk = GetCrew(iPlr);
  if(!Random(2)){
         var assaultRifle = CreateContents(AR7A, clonk);
         assaultRifle->SetAmmoPercent(100);
         CreateContents(HG7A, clonk,2);
  } else {
         var sRifle = CreateContents(SG7A, clonk);
         sRifle->SetAmmoPercent(100);
         CreateContents(CA7A, clonk,1);
         CreateContents(HG7A, clonk,2);
  }

  SetPosition(GetTeamStartPosition(GetPlayerTeam(iPlr)),GetTeamStartPosition(GetPlayerTeam(iPlr),true),clonk);
  }

func RelaunchPlayer(iPlr){

     var spawn = CreateObject(QRE1,GetTeamStartPosition(GetPlayerTeam(iPlr)),GetTeamStartPosition(GetPlayerTeam(iPlr),true),iPlr);
     var clonk = CreateObject(SF7A,20,20,iPlr);
     MakeCrewMember(clonk,iPlr);
     SetCursor(iPlr,clonk);
     clonk->~DoEnergy(100);
     spawn->~Set(clonk,iPlr,1);
     Enter(spawn,clonk);
  if(!Random(2)){
         var assaultRifle = CreateContents(AR7A, clonk);
         LocalN("ammo", assaultRifle) = 100;
         LocalN("qGrenades", assaultRifle) = 100;
         CreateContents(HG7A, clonk,2);
  } else {
         var sRifle = CreateContents(SG7A, clonk);
         LocalN("ammo", sRifle) = 100;
         CreateContents(CA7A, clonk,1);
         CreateContents(HG7A, clonk,2);
  }

    return true;
}