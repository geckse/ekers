 /*-- Fog Cliffs --*/

#strict

func Initialize() {

  SetSkyParallax (0,17,19,0,0,0,0); 
  SetGamma(RGB(15,15,15),RGB(118,118,118),RGB(215,215,215));

  //Nebel
  for(var i=0;i<180;++i) 
    CreateParticle("Fog",Random(LandscapeWidth()),Random(LandscapeHeight()),0,0,RandomX(900,1700));
  
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
    CreateContents(Contents[Random(8)], spwn);
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