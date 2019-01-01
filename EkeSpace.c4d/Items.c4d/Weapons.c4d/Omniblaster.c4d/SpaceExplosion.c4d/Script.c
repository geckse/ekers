/*-- Neues Objekt --*/

#strict

local iSize;
local maxR;

func Initialize() {
	maxR = 40;   
  return(1);
}


func init(){
	iSize = maxR;
	return this;
}


func Check(){


	if(iSize > 0){ iSize-=4;

		CreateParticle("FxDoom",0,0,RandomX(-20,20),RandomX(-20,20),maxR*10,RGB(255,255,255,100));
		 
		 for(var clnk in FindObjects(Find_Distance(maxR*2,0,0,),Find_Layer(GetObjectLayer(this)),Find_NoContainer(), Find_OCF(OCF_Collectible | OCF_Living)))
		 {  
		  var angle=Angle(0,0,GetX(clnk),GetY(clnk))-90;
		  var x=Cos(angle,40);
		  var y=Sin(angle,40);
		  Fling(clnk,x,y);
		  SetPosition(GetX(clnk),GetY(clnk),clnk);
		  SetSpeed(-x,-y,clnk);
		 }
		 for(var corpse in FindObjects(Find_Distance(maxR,0,0,),Find_Layer(GetObjectLayer(this)),Find_NoContainer(), Find_Action("Dead"))) {
		 	corpse->~Zerfetz();
		 } 

	}

	if(iSize <= 0){
		  
		  for(var i = 0; i < 6; i++){
		      CreateObject(ROCK,RandomX(-20,20),RandomX(-20,20),GetOwner())->Explode(RandomX(27,31)); 
		  }
		CreateObject(ROCK,RandomX(-20,20),RandomX(-20,20),GetOwner())->Explode(RandomX(20,25)); 
		RemoveObject();
	}

}