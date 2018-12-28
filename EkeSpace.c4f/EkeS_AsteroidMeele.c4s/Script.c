/*-- Asteriod Meele --*/

#strict 2

static itemSpawns;
static itemSpawnsL;
static itemSpawnsR;

func Initialize() { 
    CreateItemSpawns();
    return(ScriptGo(1));
}

func Script1()
{
    SetMaxPlayer();
    return(1);
}

func Script2(){

    // create items in spawn points
    for(var spwn in FindObjects(Find_ID(IS7A))) {

        while(r == itemSpawnsR || !r) var r = Random(itemSpawnsL);

        if(itemSpawns[r] == NH7A || itemSpawns[r] == SG7A || itemSpawns[r] == RL7A || itemSpawns[r] == RB7A) {
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

/*------------------------------------*\
    Item Spawns
\*------------------------------------*/
func CreateItemSpawns() {

    // declare spawning items
    itemSpawns = [CA7A, OB7A, GB7A, NH7A, SG7A, GS7A, RL7A, RB7A];
    itemSpawnsL = GetLength(itemSpawns);

    // spawn points
    CreateObject(IS7A,1377,1008);
    CreateObject(IS7A,952,538);
    CreateObject(IS7A,773,759);
    CreateObject(IS7A,1162,769);
}