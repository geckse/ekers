/*-- Neues Objekt --*/

#strict

local iTime;
local maxTime;

func Initialize() {
     maxTime = RandomX(60,300);
  return(1);
}
func Check(){
 if(!GetMaterialVal ("Color", "Material", Material("Blood"))){
  RemoveObject();
  return false;
  }

 iTime++;
 if(iTime >= maxTime) RemoveObject();
 if(!GBackSolid(0,2) && (GetMaterial(-2,2) == Material("BackWall") || GetMaterial(0,2) == Material("Tunnel")) ){
  SetXDir(GetXDir()/2);
  SetYDir(GetYDir()/2);
 if(iTime < 8){
   var val = 1;
   DrawMaterialQuad("Blood-Smooth",GetX()-val,GetY(),GetX()+val,GetY(),GetX()+val,GetY()+val,GetX()-val,GetY()+val,1);
   if(!Random(80)) RemoveObject();
 } else {
   DrawMaterialQuad("Blood-Smooth",GetX(),GetY(),GetX()+2,GetY(),GetX()+2,GetY()+2,GetX()+2,GetY(),1);
   }

   } else { RemoveObject(this); }
 }

func Hit(){
 RemoveObject();
}

global func CreateSplatter(x,y,w,h,size){
 for(var i = 0; i <= 30; i++){
  CreateObject(BLOP,RandomX(-w,w),RandomX(-h,h),-1)->SetSpeed(RandomX(-size,size),RandomX(-size,size));
 }
}