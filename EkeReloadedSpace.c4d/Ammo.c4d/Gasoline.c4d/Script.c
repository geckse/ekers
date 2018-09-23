/* Benzin */

#strict

local iFuel;
local iLeck;

public func MaxFuel(){ return(6666); }

func Initialize(){
     iFuel = 6666;
}

func Activate(object clonk)
{
  var pClonk = clonk;

  var max = clonk->~MaxFuel();
  var need = max-(clonk->~GetFuel());
  if(need > 0){
    clonk->~DoFuel(need);
    Sound("FT_Reload");
    RemoveObject();
  }
  return(1);
}

func SplitMe(doof,clonk){
   for (var i = 0; i < 5; i++)
  {
    CreateContents(MO5B, clonk);
  }
  ShiftContents(clonk, true, MO5B);
  Sound("FT_Reload");
  RemoveObject();
}

func BlowUp()
{
   iLeck = 1;
   SetGraphics("2");
  return(1);
}

func Damage()
{
  if (GetDamage() < 5) return(1);
  ScheduleCall(0, "BlowUp", 1);
  return(1);
}

func ContactBottom()
{
  if (GetYDir() < 100) return(0);
  ScheduleCall(0, "BlowUp", 1);
  return(1);
}

func Hit()
{
  Sound("ClonkHit*");
  return(1);
}

func Check(){
 if(iLeck){
   if(iFuel > 1000){
    SetYDir(GetYDir()+RandomX(-2,-5));
    if(!RandomX(8)) SetXDir(GetXDir()+RandomX(3,-3));
    iFuel-=220;
    CreateParticle("Smoke2",RandomX(-4,4),RandomX(2,6),-GetXDir()/4,-GetYDir()/4,RandomX(20,80),RGB(40,20,30));
    Sound("Fuse");
    SetR(Angle(GetX(),GetY(),GetX()+GetXDir(),GetY()+GetYDir()),this());
    CastPXS("Oil",RandomX(1,3),RandomX(20,40));
   } else {
     iFuel-=40;
     if(iFuel <= 0){
        if(!RandomX(40)){
           iLeck = 0;
          Explode(RandomX(16,24));
         }
     }
   }
 }
}
