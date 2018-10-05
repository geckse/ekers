/* Lenkrakete */

local launcher; // Raketenwerfer, aus dem die Rakete kommt
local command;  // Steuerkommando, normalerweise vom SFT
local target;   // Ziel, wird nur von der Flak übergeben
local power;    // Stärke der Explosion

#strict

func Launch(rocketLauncher, flakTarget)
{
  launcher = rocketLauncher;
  target = flakTarget;
  
  if (GetID(launcher) == RL7A)
  {
    // Rakete wird vom SFT gelenkt
    command = "Straight";
    power = 50;
  }
  if (GetID(launcher) == FK7A)
  {
    // Ziel verfolgen
    command = "Follow";
    power = 30;

    // Raketen aus der Flak sehen anders aus
    SetGraphics("TypeB");
  }
  if (!launcher)
  {
    // Fehlzündung durch Erschütterung
    command = "Random";
    power = 50;
  }
  SetAction("Fly");
  Sound("JP_Launch");
  return(1);
}

func Flying()
{
  if ((GetActTime() > 500) || (InLiquid()))
  {
    if (GetID(launcher) == RL7A) LocalN("guiding", launcher) = 0;
    SetAction("Tumble");
    return(1);
  }
  if (command == "Follow")   SetRDir(GetFollowRDir());
  if (command == "Straight") SetRDir(0);
  if (command == "Left")     SetRDir(-10);
  if (command == "Right")    SetRDir(+10);
  if (command == "Random")   SetRDir(BoundBy(RandomX(-10, 10) + GetRDir(), -25, 25));
  if (command == "Explode")  return(BlowUp());

  SetXDir(Sin(GetR(), 50));
  SetYDir(-Cos(GetR(), 50));

  if (target)
  {
    // Ziel eingeholt -> Sprengsatz zünden!
    if (ObjectDistance(target) < 10) return(BlowUp());
  }
  else if (!LocalN("guiding", launcher))
  {
    if (EkeFindVictim(-5, -10, 10, 20)) return(BlowUp());
  }
  // Resttreibstoff dem fernsteuernden SFT anzeigen
  else ShowFuelLevel();

  var offset = 10;
  if (launcher && GetActTime() < 3) offset += 20;
  
  CreateSmokeFX(offset);
  CreateFireFX(offset - 5);
  return(1);
}

func ShowFuelLevel()
{
  var clonk = Contained(launcher);
 
  if (!clonk)                                              return;
  if (GetComDir(clonk) != COMD_Stop())                     return;
  if (!WildcardMatch(GetAction(clonk), "RocketLauncher*")) return;

  clonk -> SetAmmoBar((500 - GetActTime()) / 5);
}

func GetFollowRDir()
{
  // geradeaus weiter fliegen
  if (!target) return(0);

  var x1 = GetX();
  var y1 = GetY();
  var x2 = GetX(target);
  var y2 = GetY(target);

  var angle1 = Angle(x1, y1, x2, y2);
  var angle2 = GetR() - 180;
  var angle3 = angle1 - angle2;

  if (angle3 > 360) angle3 -= 360;
  if (angle3 < 000) angle3 += 360;

  angle3 = BoundBy(angle3, 90, 270);
  return(Sin(angle3, -10));
}

func CreateSmokeFX(offset)
{
  var n = "EkeSmoke";
  var a = Random(5) + 5;
  var l = 10;

  var x = -Sin(GetR(), offset);
  var y = +Cos(GetR(), offset);

  var sMin = 40;
  var sMax = 80;

  var cMin = RGBa(255, 255, 255, 100);
  var cMax = RGBa(255, 255, 255, 200);

  CastParticles(n, a, l, x, y, sMin, sMax, cMin, cMax);
  return(1);
}

func CreateFireFX(offset)
{
  var n = "Fire2";
  var a = Random(10) + 10;
  var l = 20;

  var x = -Sin(GetR(), offset);
  var y = +Cos(GetR(), offset);

  var sMin = 25;
  var sMax = 75;

  var cMin = RGBa(255, 200, 000, 200);
  var cMax = RGBa(255, 255, 150, 150);

  CastParticles(n, a, l, x, y, sMin, sMax, cMin, cMax);
  return(1);
}

func Tumbling()
{
  if (InLiquid())
  {
    if (GetXDir() > 0)  SetXDir(GetXDir() - 1);
    if (GetXDir() < 0)  SetXDir(GetXDir() + 1);
    if (GetYDir() > 25) SetYDir(25);

    if (!Random(3)) Bubble();
  }
  SetR(Angle(0, 0, GetXDir(), GetYDir()));
  return(1);
}

func BlowUp()
{
  if (command)
  {
    // Sprengsatz zünden
    Schedule("Explode(power)", 1);
  }
  else
  {
    // Fehlzündung
    Launch();
  }
  return(1);
}

func Damage()
{
  if (GetDamage() < 1) return(1);
  return(BlowUp());
}

func Hit()
{
  return(BlowUp());
}

func Destruction()
{
  if (GetID(launcher) == RL7A) LocalN("guiding", launcher) = 0;
  return(1);
}

func RejectEntrance()
{
  if (command) return(true);
}