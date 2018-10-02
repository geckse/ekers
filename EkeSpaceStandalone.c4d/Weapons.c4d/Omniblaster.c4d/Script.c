/* Omniblaster */

#strict

// mode = Time || Shock || Enemy || Anchor
local mode;
local spikes;
local countdown;

func Initialize()
{
  mode = "Time";
  return(1);
}

func ControlSpecial2(object clonk)
{
  // Zugriff verweigert?
  if (AccessDenied(clonk)) return(1);

  var newAction;
  var newMode;

  if (mode == "Time")
  {
    newAction = "SteadyFlash";
    newMode = "Shock";
  }
  if (mode == "Shock")
  {
    newAction = "SteadyFlash";
    newMode = "Enemy";
  }
  if (mode == "Enemy")
  {
    newAction = "SingleFlash";
    newMode = "Anchor";
  }
  if (mode == "Anchor")
  {
    newAction = "SingleFlash";
    newMode = "Time";
  }
  if (GetAction() eq "Countdown") Message("Stop", this());
  SetAction(newAction);
  mode = newMode;
  clonk -> ScrollHud(mode);
  return(1);
}

func Activate(clonk)
{
  // Zugriff verweigert?
  if (AccessDenied(clonk)) return(1);
  
  if (mode == "Time")
  {
    if (GetAction() eq "Countdown")
    {
      SetAction("SingleFlash");
      Message("Stop", this());
    }
    else
    {
      SetAction("Countdown");
    }
  }
  if (mode == "Anchor")
  {   
    if (spikes)
    {
      SetPicture(0, 7, 35, 35);
      spikes = 0;
    }
    else
    {
      SetPicture(35, 7, 35, 35);
      spikes = 1;
    }
    Sound("OB_Spikes");
  }
  return(1);
}

func AccessDenied(clonk)
{
  if (Hostile(GetOwner(), GetOwner(clonk), 1))
  {
    PlayerMessage(GetOwner(clonk), "$Access$", this());
    Sound("Error");
    return(1);
  }
  return(0);
}

func EnemyCheck()
{
  if (mode != "Enemy")        return(0);
  if (Contained(Contained())) return(0);

  for (var victim in FindObjects(Find_Distance(15), Find_NoContainer()))
  {
    var b1 = GetOCF(victim) & OCF_CrewMember();
    var b2 = Hostile(GetOwner(), GetOwner(victim), 1);

    var b3 = GetOCF(victim) & OCF_Alive();
    var b4 = GetID(victim) != ZAP1;

    if ((b1 && b2) || (!b1 && b3 && b4)) BlowUp();
  }
  return(1);
}

func Countdown()
{
  if (GetAction() ne "Countdown") return(0);
  
  if (countdown < 10)
  {
    Message("@%d", this(), 10 - countdown);
    countdown++;
  }
  else
  {
    BlowUp();
  }  
  return(1);  
}

func BlowUp()
{
  Schedule("Explode(50)", 1);
  return(1);
}    

func Hit()
{
  if (mode == "Shock")
  {
    BlowUp();
    return(1);
  }
  if (spikes)
  {
    // Omniblaster festkleben
    SetSolidMask(3, 3, 1, 2, 3, 4);
  }
  Sound("MetalHit*");
  return(1);
}

func Damage()
{
  if (GetDamage() < 1) return(1);
  return(BlowUp());
}

func Entrance(clonk)
{
  if (spikes) SetSolidMask();  
  return(1);
}

func GPEDBlasterSelection(gped, query)
{
  if (query)
  {
    if (Hostile(GetOwner(), GetOwner(gped), 1)) return(0);

    // kann vom GPED gefunden werden
    return(1);
  }
  if (GetAction() eq "Countdown") Message("Stop", this());

  if (GetAction() eq "SteadyFlash")
  {
    SetAction("SteadyFlash");
  } 
  else
  {
    SetAction("SingleFlash");
  }
  Sound("OB_Select");
  return(1); 
}