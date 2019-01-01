/*-- Twiface --*/

#strict 2

static itemSpawns;
static itemSpawnsL;
static itemSpawnsR;

static clonkSpawns;
static clonkSpawns2;

func Initialize() {
    // team IDs starten bei 1
    ctfRule->SetFlagPositions([0, [288, 464], [1428, 464]]);

    // Sternenhimmel
    SetSkyParallax(0, 50,50, 1,0);

    // item spawner erzeugen
    CreateItemSpawns();

    // clonk spawnpositionen festlegen
    clonkSpawns = [
        [224, 380],
        [224, 530]
    ];
    clonkSpawns2 = [
        [1493, 380],
        [1493, 530]
    ];

    return(ScriptGo(1));
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

func GetClonkSpawn(iTeam) {

    var r = Random(2)^((FrameCounter()/100)%2);

    if(iTeam == 1) {

        return clonkSpawns[r];
    }
    else {

        return clonkSpawns2[r];
    }
}

func InitializePlayer(iPlr) {

    var clonk = GetCrew(iPlr);

    SpawnClonk(clonk, iPlr);
}

func RelaunchPlayer(iPlr) {

    var clonk = CreateObject(SF7A);

    SpawnClonk(clonk, iPlr);
}

func SpawnClonk(clonk, iPlr) {

    var spawnPos = GetClonkSpawn(GetPlayerTeam(iPlr));

    SetPosition(spawnPos[0], spawnPos[1], clonk);
    MakeCrewMember(clonk,iPlr);
    SetCursor(iPlr,clonk);
    clonk->~DoEnergy(100);

    var rifle = CreateContents(AR7A, clonk);

    rifle->SetAmmoPercent(100);
    
    SetController(NO_OWNER, clonk);
}

/*------------------------------------*\
    Item Spawns
\*------------------------------------*/
func CreateItemSpawns() {

    // declare spawning items
    itemSpawns = [CA7A, OB7A, CA7A, NH7A, SG7A, GS7A, RL7A, RB7A];
    itemSpawnsL = GetLength(itemSpawns);

    // spawn points
    CreateObject(IS7A,288,340);
    CreateObject(IS7A,1430,340);
    CreateObject(IS7A,345,620);
    CreateObject(IS7A,1375,620);
    CreateObject(IS7A,845,680);
}