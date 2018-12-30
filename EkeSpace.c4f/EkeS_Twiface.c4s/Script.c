/*-- Twiface --*/

#strict 2

static itemSpawns;
static itemSpawnsL;
static itemSpawnsR;

func Initialize() {
    // team IDs starten bei 1
    ctfRule->SetFlagPositions([0, [288, 464], [1428, 464]]);

    // Sternenhimmel
    SetSkyParallax(0, 50,50, 1,0);

    // item spawner erzeugen
    CreateItemSpawns();

    return(ScriptGo(1));
}

func GetTeamStartPosition(iTeam, fY)
{
    if(iTeam==1) { if(!Random(2)){
        if(!fY) return(288);
        return(333);
    } else {
        if(!fY) return(316);
        return(527);
    }
                 }
    if(iTeam==2) { if(!Random(2)){
        if(!fY) return(1402);
        return(333);
    } else {
        if(!fY) return(1429);
        return(527);
    }
                 }
}

func Script2(){

    // create items in spawn points
    for(var spwn in FindObjects(Find_ID(IS7A))) {

        while(r == itemSpawnsR || !r) var r = Random(itemSpawnsL);

        if(itemSpawns[r] == NH7A || itemSpawns[r] == RL7A || itemSpawns[r] == SG7A) {
            if(!Random(2)) {
                r = Random(itemSpawnsL);
            }
        }

        CreateContents(itemSpawns[r], spwn);

        itemSpawnsR = r;
    }
}
func Script120(){
    goto(2);
}

func InitializePlayer(iPlr) {
    var clonk = GetCrew(iPlr);
    var assaultRifle = CreateContents(AR7A, clonk);
    assaultRifle->SetAmmoPercent(100);
    CreateContents(HG7A, clonk,2);
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
    return true;
}

/*------------------------------------*\
    Item Spawns
\*------------------------------------*/
func CreateItemSpawns() {

    // declare spawning items
    itemSpawns = [CA7A, OB7A, GB7A, NH7A, SG7A, GS7A, RL7A, RB7A];
    itemSpawnsL = GetLength(itemSpawns);

    // spawn points
    CreateObject(IS7A,288,340);
    CreateObject(IS7A,1430,340);
    CreateObject(IS7A,345,620);
    CreateObject(IS7A,1375,620);
    CreateObject(IS7A,845,680);
}