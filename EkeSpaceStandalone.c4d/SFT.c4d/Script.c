/* SFT */

#strict

#include CLNK
#include HU7A
#include JB4K

local pistol;

protected func Initialize()
{
  // Kontextmenü-Regel aktivieren
  if (!ObjectCount(CM7A)) CreateObject(CM7A, 0, 0, NO_OWNER);

  // Munition der integrierten Pistole aufladen
  AddEffect("SellCheck", this, 1, 35, this());
  
  // weiter mit überladener Funktion
  return(inherited());
}

protected func Recruitment()
{  
  // richtigen Werte gleich zu Beginn
  SetAmmoBar(LocalN("ammo", Contents()));

  // weiter mit überladener Funktion
  return(inherited());
}

protected func ControlLeft()
{
  // im Sprung mit/ohne Waffe...
  if (WildcardMatch(GetAction(), "*Jump"))
  {
    // ggf. Richtung ändern
    if (GetDir() != DIR_Left) SetDir(DIR_Left);
  }

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlLeft")) return(1);

  // Keine überladene Steuerung
  return(0);
}

protected func ControlLeftDouble()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlLeftDouble")) return(1); 
  
  // Keine überladene Steuerung
  return(0);
}

protected func ControlRight()
{
  // im Sprung mit/ohne Waffe...
  if (WildcardMatch(GetAction(), "*Jump"))
  {
    // ggf. Richtung ändern
    if (GetDir() != DIR_Right) SetDir(DIR_Right);
  }

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlRight")) return(1);

  // Steuerung an Harpune weitergeben
  Control2Harpoon("ControlRight");

  // Keine überladene Steuerung
  return(0);
}

protected func ControlRightDouble()
{

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlRightDouble")) return(1); 
  
  // Keine überladene Steuerung
  return(0);
}

protected func ControlUp()
{
  // Schlag mit dem Kopf beim Nahkampf
  if (GetAction() eq "Fight")
  {
    SetAction("Headbang");
    return(1);
  }
  
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlUp")) return(1);

  // Steuerung an Harpune weitergeben
  Control2Harpoon("ControlUp");

  // Keine überladene Steuerung
  return(0);
}

protected func ControlDown()
{

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlDown")) return(1);

  // Steuerung an Harpune weitergeben
  Control2Harpoon("ControlDown");

  // Keine überladene Steuerung
  return(0);
}

protected func ControlDownDouble()
{
  // Steuerung an Harpune weitergeben
  //Control2Harpoon("ControlDownDouble");

  // Keine überladene Steuerung
  return(0);
}

protected func ControlThrow()
{
  // Schlagen beim Nahkampf
  if (GetAction() eq "Fight")
  {
    SetAction("Punch");
    return(1);
  }
  // Bei vorherigem Doppel-Stop nur Ablegen   
  if (GetPlrDownDouble(GetOwner())) return(0);

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlThrow")) return(1); 
 
  // Keine überladene Steuerung
  return(0);
}

protected func ControlThrowDouble()
{
  ControlThrow();
  return(1);
}

protected func ControlDig()
{
  // Kicken beim Nahkampf
  if (GetAction() eq "Fight")
  {
    SetAction("Kick");
    return(1);
  }
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlDig")) return(1);

  // Keine überladene Steuerung
  return(0);
}

protected func ControlDigSingle()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlDigSingle")) return(1); 

  // Keine überladene Steuerung
  return(0);
}

protected func ControlDigDouble()
{
  if (WildcardMatch(GetAction(), "*Walk")) return(0);
  if (WildcardMatch(GetAction(), "*Swim")) return(0);
  if (GetAction() eq "Dig")                return(0);
  if (GetAction() eq "Push")               return(0);
  if (GetAction() eq "Kick")               return(0);

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("Activate")) return(1); 

  // Keine überladene Steuerung
  return(0);
}

protected func ControlSpecial()
{  
  // ggf. Pistole wegstecken
  if (FindContents(PT7A))
  {
    Holster();
    return(0);
  }
  // Inventar verschieben
  ShiftContents(0, 0, 0, 1);
  
  // Bewaffnung prüfen
  CheckArmed();
  return(1);
}

protected func ControlSpecialDouble()
{
  ControlSpecial();
  return(1);
}

protected func ControlSpecial2()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlSpecial2"))
  {
    Sound("SF_Mode");
    return(1);
  }
  // bei angefassten Objekten Holen ermöglichen
  if (GetAction() eq "Push")
  {
    var stuff = GetActionTarget();
    if (GetDefCoreVal("GrabPutGet", "DefCore", GetID(stuff)) > 1)
    {
      SetCommand(0, "Get", GetActionTarget(), 0, 0, 0, 1);
      return(1);
    }
  }
  Holster();
  return(0);
}

protected func ControlSpecial2Double()
{
  ControlSpecial2();
  return(1);
}

private func Control2Contents(string command)
{
  // angefasste Objekte haben Vorrang, außer bei Modus-Auswahl
  if ((GetAction() eq "Push") && (command != "ControlSpecial2")) return(0);

  var result = ObjectCall(Contents(), command, this());
  return(result);
}

private func Control2Harpoon(string command)
{
  var harpoon = FindObject2(Find_Container(this()), Find_ID(HP7A), Find_Action("Reel"));
  if (harpoon) LocalN("ropeCommand", harpoon) = command;
}

protected func ContactLeft()
{
  // nicht weiter bei Kontakt am Spielfeldrand
  if (!GetContact(0, -1, CNAT_Left)) return(0);

  FallDamage();
  
  if (GetAction() eq "JetpackFly")
  {
    SetComDir(COMD_Stop());
    SetAction("Scale");
  }
  return(1);
}

protected func ContactRight()
{
  // nicht weiter bei Kontakt am Spielfeldrand
  if (!GetContact(0, -1, CNAT_Right)) return(0);  

  FallDamage();
  
  if (GetAction() eq "JetpackFly")
  {
    SetComDir(COMD_Stop());
    SetAction("Scale");
  }
  return(1);
}

protected func ContactTop()
{
  FallDamage();
  
  if (GetAction() eq "JetpackFly")
  {
    SetComDir(COMD_Stop());
    SetAction("Hangle");
  }
  return(1);
}

protected func ContactBottom()
{
  FallDamage();
  
  if (GetAction() eq "JetpackFly")
  {
    SetComDir(COMD_Stop());
    SetAction("JetpackWalk");
  }
  return(1);
}

private func FallDamage()
{
  // weiter nur wenn der Clonk noch lebt
  if(!GetAlive()) return(0);

  var speed = Max(Abs(GetXDir()), Abs(GetYDir()));

  if (speed >= 70)
  {
    DoEnergy((70 - speed) * 2);
    Sound("Hurt*");
  } 
  return(1);
}

private func CheckArmed()
{

  ScrollHud(LocalN("mode", Contents()));
  SetAmmoBar(LocalN("ammo", Contents()));
  if(ammoBar) SetPhase(LocalN("ammo", Contents()), ammoBar);

  if (GetAction() eq "Walk") if (GetID(Contents()) == PT7A) return(SetActionSmooth("PistolWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == PT7A) return(SetActionSmooth("PistolJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == PT7A) return(SetActionSmooth("PistolJump"));
  if (GetAction() eq "PistolWalk") if (GetID(Contents()) != PT7A) return(SetActionSmooth("Walk"));
  if (GetAction() eq "PistolJump") if (GetID(Contents()) != PT7A) return(SetActionSmooth("Jump"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == AR7A) return(SetActionSmooth("AssaultRifleWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == AR7A) return(SetActionSmooth("AssaultRifleJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == AR7A) return(SetActionSmooth("AssaultRifleJump"));
  if (GetAction() eq "AssaultRifleWalk") if (GetID(Contents()) != AR7A) return(SetActionSmooth("Walk"));
  if (GetAction() eq "AssaultRifleJump") if (GetID(Contents()) != AR7A) return(SetActionSmooth("Jump"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == RL7A) return(SetActionSmooth("RocketLauncherWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == RL7A) return(SetActionSmooth("RocketLauncherJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == RL7A) return(SetActionSmooth("RocketLauncherJump"));
  if (GetAction() eq "RocketLauncherWalk") if (GetID(Contents()) != RL7A) return(SetActionSmooth("Walk"));
  if (GetAction() eq "RocketLauncherJump") if (GetID(Contents()) != RL7A) return(SetActionSmooth("Jump"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == SG7A) return(SetActionSmooth("ShotgunWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == SG7A) return(SetActionSmooth("ShotgunJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == SG7A) return(SetActionSmooth("ShotgunJump"));
  if (GetAction() eq "ShotgunWalk") if (GetID(Contents()) != SG7A) return(SetActionSmooth("Walk"));
  if (GetAction() eq "ShotgunJump") if (GetID(Contents()) != SG7A) return(SetActionSmooth("Jump"));

}

private func SetActionSmooth(newAction)
{
  var phase = GetPhase();
  SetAction(newAction);
  SetPhase(phase);
}

private func SetAmmoBar(int percent)
{
  ResetPhysical();
  DoMagicEnergy(0);

  SetPhysical("Magic", 100000, 2);
  DoMagicEnergy(percent);
}

private func Punching()
{
  if (!Random(3)) Sound("Kime*");
  
  Punch(GetActionTarget());
  Sound("Punch*");
  return(1);
}

private func Headbanging()
{
  if (!Random(3)) Sound("Kime*");

  var rCulprit = GetRank();
  var rVictim = GetRank(GetActionTarget());
  var rAdvantage = rCulprit - rVictim;

  if (rAdvantage >= 0)
  {
    DoEnergy(-rAdvantage, GetActionTarget());
    Punch(GetActionTarget());
  }
  else
  {
    DoEnergy(rAdvantage);
    Sound("Hurt*");
  }
  Sound("Punch*");
  return(1);
}

private func Kicking()
{
  if (!Random(3)) Sound("Kime*");
  
  DoEnergy(-10, GetActionTarget());
  Fling(GetActionTarget(), 4 * GetDir() - 2, -1);
  SetComDir(COMD_Stop()); 
  Sound("Punch*");
  return(1);
}

private func Chopping()
{
  if (GetActTime())
  {
    DoDamage(500, GetActionTarget());
  }
  else
  {
    Sound("Chop*");
  }
  return(1);
}

private func Building()
{
  if (GetAction() eq "Build")
  {
    // Funken und bläuliches Licht
    WeldingFX(20 * GetDir() - 10, 8);    

    // Maske ab, Schweißnaht checken
    if (!Random(10)) SetAction("WeldingMaskDown");
  }  
  else
  {
    // Maske auf, Schweißen!
    if (!Random(10)) SetAction("WeldingMaskUp");
  }
  return(1);
}

private func WeldingFX(xPos, yPos)
{
  CreateParticle("MSpark", xPos, yPos, RandomX(-15, 15), Random(15) * -1, 15, RGB(255, 255, 255));
  CreateParticle("MSpark", xPos, yPos, RandomX(-20, 20), Random(20) * -1, 15, RGB(255, 255, 255));
  CreateParticle("MSpark", xPos, yPos, RandomX(-25, 25), Random(25) * -1, 15, RGB(255, 255, 255));  

  CreateParticle("PSpark", xPos, yPos, RandomX(-1, 1), RandomX(-1, 1), RandomX(25, 50), RGB(Random(255), 255, 255));
  CreateParticle("PSpark", xPos, yPos, RandomX(-1, 1), RandomX(-1, 1), RandomX(100, 250), RGBa(Random(255), 255, 255, 150));
}

private func JetpackFX()
{
  var xPos = -14 * GetDir() + 7;
  var yPos = 1; 
 
  CreateParticle("PSpark", xPos, yPos, 0, 0, RandomX(25, 50), RGB(Random(255), 255, 255));
}

private func Holster()
{
  // Pistole wegwerfen, weiter mit Ejection()
  if (FindContents(PT7A)) return(Exit(pistol));

  if (!pistol)
  {
    pistol = CreateContents(PT7A);
    LocalN("ammo", pistol) = 100;
  }
  else
  {
    Enter(this(), pistol);
  }
  ShiftContents(0, true, PT7A);
  CheckArmed();
  Sound("SF_Holster");
  return(1);  
}

func FxSellCheckTimer()
{
  // weg, wenn Gebäude keine Heimatbasis ist
  // oder der Besitzer nicht genug Kohle hat;

  if (!pistol) return;

  var case = Contained();
  if (!case) return;

  var baseOwner = GetBase(case);
  if (baseOwner < 0)                     return;
  if (Hostile(baseOwner, GetOwner(), 1)) return;

  var ammo = LocalN("ammo", pistol);
  if (ammo == 100) return;

  var cashNeed = (100 - ammo) / 20;
  var cashHave = GetWealth(baseOwner);

  var ammoNeed = 100 - ammo;
  var ammoHave = cashHave * 20;

  ammo += Min(ammoNeed, ammoHave);
  LocalN("ammo", pistol) = ammo;
  if (Contained(pistol) == this()) SetAmmoBar(ammo);

  DoWealth(baseOwner, -Min(cashNeed, cashHave));
  if (Min(cashNeed, cashHave)) Sound("UnCash");
}

protected func ContentsDestruction()
{
  ScheduleCall(0, "CheckArmed", 1);
}

func RejectCollect(id idObject, object pObject)
{
  // nicht mehr als 5 Objekte tragbar
  if (ContentsCount() >= 5) return(1);
  return (0);
}

protected func Collection2(stuff)
{   
  if (ContentsCount(GetID(stuff)) == 1)
  {
    // hinten an die Inventarliste hängen
    if (GetID(stuff) != PT7A) ShiftContents();
  }
  // Bewaffnung prüfen
  CheckArmed();
  return(1);
}

protected func Ejection(stuff)
{
  if (GetID(stuff) == PT7A)
  {
    var hud = FindObjectOwner(IM7A, GetOwner());
    Enter(hud, pistol);
    Sound("SF_Holster");
  }
  // Bewaffnung prüfen
  CheckArmed();
  return(1);
}

protected func Death()
{ 

  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this(), GetKiller());
  
  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return(0);
  
  Sound("SF_Die");
  DeathAnnounce();

  // Letztes Mannschaftsmitglied tot?
  if (!GetCrew(GetOwner())) GameCallEx("RelaunchPlayer", GetOwner(), this());

  // Tod dem Spiel(ziel) berichten
  GameCallEx("ReportHomicide", GetKiller(), GetOwner(), GetID(this));
  return _inherited(...);
}