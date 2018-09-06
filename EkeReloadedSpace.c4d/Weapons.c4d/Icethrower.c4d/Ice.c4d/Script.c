/* Feuer */

#strict

local culprit;
local direction;
local yDifference;

func Launch(object clonk, int dir, int yDiff)
{
  culprit = clonk;
  direction = 2 * dir - 1;
  yDifference = yDiff;

  SetXDir(direction * 50);
  SetAction("Fly");
  return(1);
}

func Flying()
{
  var flightTime = GetActTime();
  if (flightTime > RandomX(15, 25)) RemoveObject();

  for (var victim in FindObjects(Find_Distance(10), Find_NoContainer()))
  {
    if (BurnLiving(victim))      return(0);
    if (BurnTin(victim))         return(0);
    if (BurnInflammable(victim)) return(0);
    //if (MeltIce(victim))   return(0);
  }
  // Feuer-FX hinzuf�gen
  for (var i = 0; i < 8; i++)
  {
    var x = direction * i * 2;
    var y = 1 - ((yDifference / 4) * i);

    var xDir = direction * (50 - flightTime);
    var yDir = RandomX(-flightTime * 2, 0);

    var size = 30 + (flightTime * (Random(5) + 1));
    var color = RGBa(225, 225, 255, 255 - size);
    if(!Random(2)) color = RGBa(205-RandomX(0,60), 205-RandomX(0,60), 255-RandomX(0,40), 255 - size);
    CreateParticle("ColorFire2", x, y, xDir, yDir, size, color);
  }
  return(1);
}

func Splashing()
{

  RemoveObject();
  return(1);
}

func Hit()
{

  return(1);
}

func BurnLiving(victim)
{
  var p1 = GetController();
  var p2 = GetController(victim);

  if (ObjectCount(NF5B) && !Hostile(p1, p2, 1))          return(0);
  if (((GetX(victim) - GetX(culprit)) * direction) <= 0) return(0);
  if (!(GetOCF(victim) & OCF_Alive()))                   return(0);

  if (GetOCF(victim) & OCF_Alive())
  {
    victim->~DoTemperature(-RandomX(1,5));
    if(!Random(3)){
      if(victim->~GetTemperature() < 13) Freeze(victim,GetCrew(GetController()));
    }
  }
  DoEnergy(-1, victim);
  if (GetMass(victim) < 500) Fling(victim, direction * 2, -1);

  RemoveObject();
  return(1);
}

func BurnTin(victim)
{
  if (GetOCF(victim) & OCF_Alive())           return(0);
  if (GetCategory(victim) & C4D_StaticBack()) return(0);
  if (GetCategory(victim) & C4D_Structure())  return(0);

  if (!PrivateCall(victim, "Damage")) return(0);

  if (GetOCF(victim) & OCF_OnFire()) Extinguish (victim);

  DoDamage(1, victim);

  RemoveObject();
  return(1);
}

func BurnInflammable(victim)
{
  if (GetOCF(victim) & OCF_Alive())          return(0);
  if (!(GetOCF(victim) & OCF_Inflammable())) return(0);

  //Incinerate(victim);

  //RemoveObject();
  return(1);
}
