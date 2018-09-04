/*-- Arena Field --*/

#strict

local iArea;
local iMod;
local icon;

func Initialize() {
   iArea = 500;
   iMod = 0;
   SetArea(RandomX(70,350),2);
  return(1);
}

public func SetArea(size,mod){
  if(size > 500) size = 500;
  if(size < 20) size = 20;
  iArea = size;
  iMod = mod;
    SetCon(iArea/5);

  if(!icon) icon = CreateObject(ASF1,0,0,-1);
  var x = GetX();
  var y = GetY();
  icon->SetPosition(x,y);

  if(iMod == 0){
    SetClrModulation(RGBa(255,100,20,128), this());
    icon->SetGraphics("");
  }
  if(iMod == 1){
    SetClrModulation(RGBa(255,200,0,128), this());
    icon->SetGraphics("2");
  }
  if(iMod == 2){
    SetClrModulation(RGBa(255,255,255,128), this());
    icon->SetGraphics("3");
  }
}

public func Check(){
 for(var pClonk in FindObjects(Find_Distance(iArea/2), Find_OCF(OCF_CrewMember), Find_NoContainer () )) {
   if(pClonk){
     if(iMod == 0) pClonk->~DoFuel(30);
     if(iMod == 1 && !Random(3)){
       if(GetID(Contents(0,pClonk)) == AR5B){
        if(LocalN("ammo", Contents(0,pClonk)) < 100) LocalN("ammo", Contents(0,pClonk)) += 5;
        if(LocalN("qGrenades", Contents(0,pClonk)) < 100) LocalN("qGrenades", Contents(0,pClonk)) += 5;
        pClonk -> SetAmmoBar(LocalN("ammo",Contents(0,pClonk)));
       }
       if(GetID(Contents(0,pClonk)) == SG5B){
        if(LocalN("ammo", Contents(0,pClonk)) < 100) LocalN("ammo", Contents(0,pClonk)) += 5;
        pClonk -> SetAmmoBar(LocalN("ammo",Contents(0,pClonk)));
       }
       if(GetID(Contents(0,pClonk)) == FT5B){
        if(LocalN("ammo", Contents(0,pClonk)) < 100) LocalN("ammo", Contents(0,pClonk)) += 5;
        pClonk -> SetAmmoBar(LocalN("ammo",Contents(0,pClonk)));
       }
       if(GetID(Contents(0,pClonk)) == RL5B){
        if(LocalN("ammo", Contents(0,pClonk)) < 100) LocalN("ammo", Contents(0,pClonk)) += 5;
        pClonk -> SetAmmoBar(LocalN("ammo",Contents(0,pClonk)));
       }
       if(GetID(Contents(0,pClonk)) == UZ5B){
        if(LocalN("ammo", Contents(0,pClonk)) < 100) LocalN("ammo", Contents(0,pClonk)) += 5;
        pClonk -> SetAmmoBar(LocalN("ammo",Contents(0,pClonk)));
       }
       if(GetID(Contents(0,pClonk)) == PT5B){
        if(LocalN("ammo", Contents(0,pClonk)) < 100) LocalN("ammo", Contents(0,pClonk)) += 5;
        pClonk -> SetAmmoBar(LocalN("ammo",Contents(0,pClonk)));
       }
       if(GetID(Contents(0,pClonk)) == IT5B){
        if(LocalN("ammo", Contents(0,pClonk)) < 100) LocalN("ammo", Contents(0,pClonk)) += 5;
        pClonk -> SetAmmoBar(LocalN("ammo",Contents(0,pClonk)));
       }
     }
     if(iMod == 2) {
         pClonk->~DoFuel(30);
         SetOwner(GetOwner(pClonk), this());
		 SetClrModulation(GetTeamColor(GetPlayerTeam(GetOwner(pClonk))), this());
     }
   }
 }
}
