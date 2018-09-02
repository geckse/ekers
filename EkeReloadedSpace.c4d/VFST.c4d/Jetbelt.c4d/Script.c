/*-- Jetbelt --*/

#strict 2

local fuel, slow, cdir, effectnum;
local jGrab;

protected func Initialize() {
  effectnum = AddEffect("Jetbelt", this, 100, 0, this);
  // Treibstoff f�llen
  fuel = MaxFuel();
  // HUD-Update
  //this -> UpdateHUDValue(HUD_Fuel, GetFuel() * 100 / MaxFuel());
  return _inherited(...);
}

private func Active() {
  return ChangeEffect(0, this, effectnum, GetEffect(0, this, effectnum, 1), 1);
}

private func StandBy() {
  return ChangeEffect(0, this, effectnum, GetEffect(0, this, effectnum, 1), 0);
}

/* Einstellungen */
private func MaxSpeed(){return(22);}
private func MaxAccel(){return(120);}//iPrec = 100
private func MaxFuel() {return 6666;}//iPrec = 100
private func Consumption(){
      if(!FindObject(META)){ return 5; } else { return 20; }
}//iPrec = 100
private func PushConsumption(){return 1;}//iPrec = 1000

public func IsActive()
{
  return GetEffect(0, this, effectnum, 3);
}

/* Steuerung */
public func ControlUpDouble(){_inherited(...); return(Switch(COMD_Up));}
//public func ControlDownDouble(){_inherited(...); return(Switch(COMD_Down));}
public func ControlLeftDouble(){_inherited(...); SetDir(DIR_Left); return(Switch(COMD_Left));}
public func ControlRightDouble(){_inherited(...); SetDir(DIR_Right); return(Switch(COMD_Right));}

public func ControlUp(){_inherited(...); if(IsActive() && noRola())return(Start(COMD_Up));}
public func ControlDown(){_inherited(...); if(IsActive() && noRola())return(Start(COMD_Down));}
public func ControlLeft(){_inherited(...); if(IsActive() && noRola())return(Start(COMD_Left));}
public func ControlRight(){_inherited(...); if(IsActive() && noRola())return(Start(COMD_Right));}

global func GrabPush() {
  return GetDefGrab(GetID()) == 1;
}

public func Slow(){if(IsActive())return(Start(COMD_Stop));}

public func ControlUpdate(){if(IsActive() && noRola())return(Start(GetComDir()));}

private func Switch(int iDir)
{
  //Log("Dir: %s", ComDir2String(iDir));
  if(IsActive())
  {
    if(iDir == COMD_Up)
      Stop();
  }
  else
  {
    Start(iDir);
  }
}

private func Stop()
{
  if(IsActive())
  {
    Sound("Jetbelt",0,this,0,0,-1);
    Sound("JetbeltStop");

    SetPhysical("CanScale", 1, PHYS_Temporary);
    SetPhysical("CanHangle", 1, PHYS_Temporary);
  }

  StandBy();
  cdir = COMD_None;

  jGrab = 0;

  return;
}

private func Start(int iDir)
{
  if(!IsReady()) return;
  if(Frozen(this)) return;

  var jnr = GetPlrCoreJumpAndRunControl(GetController());

  if(iDir == COMD_Stop)
  {
    if(!jnr)
      slow = !slow;
    else
      slow = true;

    return;
  }
  else
  {
    if(jnr)
      slow = false;

  }

  cdir = iDir;

  if(!IsActive())
  {
    Sound("Jetbelt",0,this,0,0,+1);
    SetUserAction();
    Active();

    //ControlDig(); // automatisch Sachen festheben

    //SetPhysical("CanScale", 0, PHYS_Temporary);
    //SetPhysical("CanHangle", 0, PHYS_Temporary);
  }
}

private func GetFuel()
{
  return fuel;
}

private func DoFuel(int iAmount)
{
  var iTemp = fuel;
  fuel = BoundBy(fuel+iAmount,0,MaxFuel());
  return fuel - iTemp;
}

private func RefillFuel() // hier evtl. Batterien aus dem Inventar umladen
{
  return(true);
}

protected func FxJetbeltTimer()
{
  if(!IsReady()) return(Stop());
  if(Frozen(this())) return(Stop());
  if(GetAction() == "Tumble") return(Stop());

  //UpdateTimer();

  if(!GetFuel()) RefillFuel();
  DoFuel(-Consumption());

  var r = ComDir2Angle(cdir);

  var xmax = MaxSpeed();
  var ymax = MaxSpeed();

  if(slow)
  {
    xmax /= 4;
    ymax /= 4;
  }

  if(!noRola()){
    xmax = 1;
    ymax = 1;
    r = 0;
  }

  var xdir = BoundBy(GetXDir()*100+Sin(r,MaxAccel()),-xmax*100,+xmax*100);
  var ydir = BoundBy(GetYDir()*100-Cos(r,MaxAccel()),-ymax*100,+ymax*100);

  SetXDir(xdir,0,1000);
  SetYDir(ydir-GetGravityAccel4K(1000),0,1000);//4K-Lib sorgt f�r Pseudo-Schwerelosigkeit. ;D

  if(jGrab) {
    if(ObjectDistance(jGrab) > Distance(GetDefWidth(jGrab -> GetID()), GetDefHeight(jGrab -> GetID()))) {
      Message("%s verloren!", this, jGrab -> GetName());
      jGrab = 0;
    }
    else {
      // kostenlos, wenn die Triebwerke des Ziels aktiv sind (-> Kapsel)
      if(!jGrab -> ~IsBlowingOut())
        DoFuel(-PushConsumption() * jGrab -> GetMass() / 10);
      jGrab -> SetXDir(xdir,0,1000);
      jGrab -> SetYDir(ydir-GetGravityAccel4K(1000),0,1000);
    }
  }
    /*
  if(xdir < 0)
    SetDir(DIR_Left);
  else if(xdir > 0)
    SetDir(DIR_Right);
      */
  UpdateFuelHUD();


  r-=180;

  var dist = Distance(0,0,GetXDir(),GetYDir());
  var maxx = +Sin(r,dist/10);
  var maxy = -Cos(r,dist/10);
  var ptrdist = 50;

  for(var i=0; i<dist; i+=ptrdist)
  {
    var x = -maxx*i/dist-GetDir()*12+6;
    var y = -maxy*i/dist+3;

    var rand = RandomX(-30,30);
    var xdir = +Sin(r+rand,20);
    var ydir = -Cos(r+rand,20);

    CreateParticle("Thrust",x,y,GetXDir()/2,GetYDir()/2,RandomX(50,70),RGBa(200,200,255),this,true);
    CreateParticle("Smoke2",x,y,xdir,ydir,RandomX(40,60),RGBa(220,200,180),this,true);
  }
}

public func UpdateFuelHUD() {
 // return this -> UpdateHUDValue(HUD_Fuel, GetFuel() * 100 / MaxFuel());
}

// Clonk stirbt
protected func FxJetbeltStop(object pTarget, int iEffectNumber) {
  if(GetEffect(0, pTarget, iEffectNumber, 3)) {
    Sound("Jetbelt",0,this,0,0,-1);
    Sound("JetbeltStop");
    SetPhysical("CanScale", 1, PHYS_Temporary);
    SetPhysical("CanHangle", 1, PHYS_Temporary);
  }
}

public func IsReady()
{
  if(!GetFuel() || GetCommand() || this -> ~HeavySuit()) return;

  if(GetAction() == "Jump"
  || GetAction() == "AssaultRifleJump"
  || GetAction() == "PistolJump"
  || GetAction() == "RocketLauncherJump"
  || GetAction() == "FlamethrowerJump"
  || GetAction() == "IcethrowerJump"
  || GetAction() == "ShotgunJump"
  || GetAction() == "Tumble"
  || GetAction() == "Dive")
    return(1);
}

private func SetUserAction()
{
  if(GetAction() != "Jump")
    SetAction("Jump");
  if(GetAction() != "AssaultRifleJump")
    SetAction("AssaultRifleJump");
  if(GetAction() != "PistolJump")
    SetAction("PistolJump");
  if(GetAction() != "RocketLauncherJump")
    SetAction("RocketLauncherJump");
  if(GetAction() != "FlamethrowerJump")
    SetAction("FlamethrowerJump");
  if(GetAction() != "IcethrowerJump")
    SetAction("IcethrowerJump");
  if(GetAction() != "ShotgunJump")
    SetAction("ShotgunJump");
    }

private func ComDir2Angle(int iDir)
{
  if(iDir == COMD_Down) return(180);
  if(iDir == COMD_Left) return(270);
  if(iDir == COMD_Right) return(90);
  if(iDir == COMD_DownLeft) return(225);
  if(iDir == COMD_DownRight) return(135);
  if(iDir == COMD_UpLeft) return(315);
  if(iDir == COMD_UpRight) return(45);
  //if(COMD_Up) return(0);
  return(0);
}

private func ComDir2String(int iDir)//:D Debug!
{
  if(iDir == COMD_Stop) return("COMD_Stop");
  if(iDir == COMD_Down) return("COMD_Down");
  if(iDir == COMD_Left) return("COMD_Left");
  if(iDir == COMD_Right) return("COMD_Right");
  if(iDir == COMD_DownLeft) return("COMD_DownLeft");
  if(iDir == COMD_DownRight) return("COMD_DownRight");
  if(iDir == COMD_UpLeft) return("COMD_UpLeft");
  if(iDir == COMD_UpRight) return("COMD_UpRight");
  return("COMD_Up");
}

public func noRola(){
 var rola = this->~FindContents(RL5B);
 if(rola){
   if(rola->~IsGuided()){
      cdir = COMD_Stop;
      SetComDir(COMD_Stop,this);
    return false;
   }
 }
 return true;
}
