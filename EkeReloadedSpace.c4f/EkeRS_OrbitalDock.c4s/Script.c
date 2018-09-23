/*-- Orbital Dock --*/

#strict 2

static itemSpawns;
static itemSpawnsL;

func Initialize() {
  // Sternenhimmel
  SetSkyParallax(0, 100,70, 1,0); 

  // declare spawning items
  itemSpawns = [CA5B, OB5B, GB5B, NH5B, SG5B, MS5B, HG5B, GS5B];
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
    for(var spwn in FindObjects(Find_ID(SPNP))) {
        
        var r = Random(itemSpawnsL);
        
        // half chance for specific items
        if (itemSpawns[r] == (SG5B || NH5B)) {
            r = Random(itemSpawnsL);
        }
        CreateContents(itemSpawns[r], spwn);
   }
}
func Script120(){
     goto(2);
}

private func InitializeClonk(clonk)
{ 
    var wipf = PlaceAnimal(WIPF);
    SetPosition(GetX(wipf), GetY(wipf)-10, clonk);
    RemoveObject(wipf);

    var assaultRifle = CreateContents(AR5B, clonk);
    LocalN("ammo", assaultRifle) = 100;
    LocalN("qGrenades", assaultRifle) = 100;
    CreateContents(HG5B, clonk,1);
    return(1);
}