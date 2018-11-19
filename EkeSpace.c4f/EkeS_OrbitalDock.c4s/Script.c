/*-- Orbital Dock --*/

#strict 2

static itemSpawns;
static itemSpawnsL;

func Initialize() {
  // Sternenhimmel
  SetSkyParallax(0, 100,70, 1,0);

  // declare spawning items
  itemSpawns = [CA7A, OB7A, GB7A, NH7A, SG7A, MS7A, HG7A, GS7A, RL7A, RB7A];
  itemSpawnsL = GetLength(itemSpawns);

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

        var r = Random(itemSpawnsL);

        // half chance for specific items
        if (itemSpawns[r] == SG7A || itemSpawns[r] == NH7A || itemSpawns[r] == RL7A) {
            r = Random(itemSpawnsL);
        }
        CreateContents(itemSpawns[r], spwn);
   }
}
func Script120(){
     goto(2);
}