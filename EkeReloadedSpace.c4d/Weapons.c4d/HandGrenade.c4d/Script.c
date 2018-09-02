/* Handgranate */

#strict

protected func Initialize()
{
	// Granaten idlen jetzt standardm��ig damit sie im nach Aktvierung und anschlie�ender Deaktivierung wieder mit den anderen im Inventar stacken
	SetAction("Idle");
	SetPicture(5, 0, 35, 35);
}

func Activate(object clonk)
{
  // Zeitz�nder starten oder stoppen
  if (GetAction() eq "Activated") {
	  SetAction("Idle");
	  SetPicture(5, 0, 35, 35);
	  Sound("AB_Empty");
	  return(1);
  }
  else {
	  SetAction("Activated");
	  SetPicture(40, 0, 35, 35);
	  Sound("HG_PullPin");
	  return(1);
  }
}

func BlowUp()
{
 var pTarget = this;

  CreateObject(PEXP,0,0,GetOwner())->init(); 
  RemoveObject();
  return(1);
}     

func Damage()
{
  if (GetDamage() < 1) return(1);
  ScheduleCall(0, "BlowUp", 1);
  return(1);
}

func Hit()
{
  Sound("MetalHit*");
  return(1);
}

func FX()
{
  if (Contained()) return(0);
  if (InLiquid())  return(0);

  if (Abs(GetXDir()) + Abs(GetYDir()) > 10)
  {
    CreateParticle("PSpark", RandomX(-3, 3), RandomX(-8, -2), 0, 0, 150, RGBa(255, Random(2) * 100, 0, 120));
    CreateParticle("PSpark", RandomX(-3, 3), RandomX(-8, -2), 0, 0, 125, RGBa(255, Random(2) * 100, 0, 120));
    CreateParticle("PSpark", RandomX(-3, 3), RandomX(-8, -2), 0, 0, 100, RGBa(255, Random(2) * 100, 0, 120));
  }
  else
  {
    CreateParticle("PSpark", Random(2), RandomX(-6, -4), GetWind() / 10, -5, 40, RGBa(255, Random(2) * 100, 0, 120));
  }
  return(1);
}

