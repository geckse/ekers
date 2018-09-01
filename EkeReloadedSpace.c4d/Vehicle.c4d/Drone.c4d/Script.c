/* ---- Drone --- */

#strict 2

local Mov_Ang_Deviation;
local Mov_Speed;
local Prec_Mov_Dist;
local Stop_Dist;


local targetX, targetY;

func Initialize() {

     Mov_Ang_Deviation = 20;
     Mov_Speed = 20;
     Prec_Mov_Dist = 30;
     Stop_Dist = 2;


     ObjectSetAction(this,"Fly");
}

/* Action-Calls */

protected func Idling() {
  SetPosition(targetX, targetY + Sin(GetPhase() * 360 / GetActMapVal("Length", GetAction()), 1));
}

protected func Flying() {
  if(Distance(GetX(), GetY(), targetX, targetY) < Stop_Dist) {
    //Stop();
    return;
  }
  var angle = Angle(GetX(), GetY(), targetX, targetY);
  if(Distance(GetX(), GetY(), targetX, targetY) > Prec_Mov_Dist) {
    var angle = RandomX(angle - Mov_Ang_Deviation, angle + Mov_Ang_Deviation);
  }
  var speedX = Sin(angle, Mov_Speed);
  var speedY = -Cos(angle, Mov_Speed);
  SetSpeed(speedX, speedY);
}