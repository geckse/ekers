 /*-- Asteriod Meele --*/

#strict

func Initialize() {
  // Sternenhimmel
  SetSkyParallax(0, 100,70, 1,0);
  CreateObject(COFA);  
  return(ScriptGo(1));
}
func Script1()
{
  SetMaxPlayer();
  return(1);
}

func Script2(){
    for(var spwn in FindObjects(Find_ID(SPNP))) {
    var Contents = [CA5B, OB5B, HG5B, GB5B, NH5B, GS5B, SG5B];
    CreateContents(Contents[Random(GetLength(Contents))], spwn);
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