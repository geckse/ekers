 /*-- Asteriod Meele --*/

#strict 2

func Initialize() {
  // Sternenhimmel
  SetSkyParallax(0, 100,70, 1,0);
  CreateObject(CF7A);  
  return(ScriptGo(1));
}
func Script1()
{
  SetMaxPlayer();
  return(1);
}

func Script2(){
    for(var spwn in FindObjects(Find_ID(IS7A))) {
    var Contents = [CA7A, OB7A, HG7A, GB7A, NH7A, GS7A, SG7A];
    CreateContents(Contents[Random(GetLength(Contents))], spwn);
   }
}
func Script120(){
     goto(2);
}