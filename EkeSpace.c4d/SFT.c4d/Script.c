/* SFT */

#strict 2

#include CLNK
#include JB4K

local pistol;
local ctrlSpclCmboCnt;

protected func Initialize()
{
  // Kontextmenü-Regel aktivieren
  if (!ObjectCount(CM7A)) CreateObject(CM7A, 0, 0, NO_OWNER);

  // Munition der integrierten Pistole aufladen
  AddEffect("SellCheck", this, 1, 35, this);

  // weiter mit überladener Funktion
  return _inherited(...);
}

protected func Recruitment()
{
  // richtigen Werte gleich zu Beginn
  SetAmmoBar(Contents() && Contents()->~GetAmmoPercent());

  // weiter mit überladener Funktion
  return _inherited(...);
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
  if (Control2Contents("ControlLeft")) return true;

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlLeftDouble()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlLeftDouble")) return true;

  // Keine überladene Steuerung
  return _inherited(...);
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
  if (Control2Contents("ControlRight")) return true;

  // Steuerung an Harpune weitergeben
  Control2Harpoon("ControlRight");

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlRightDouble()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlRightDouble")) return true;

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlUp()
{
  // Schlag mit dem Kopf beim Nahkampf
  if (GetAction() == "Fight")
  {
    SetAction("Headbang");
    return true;
  }

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlUp")) return true;

  // Steuerung an Harpune weitergeben
  Control2Harpoon("ControlUp");

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlDown()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlDown")) return true;

  // Steuerung an Harpune weitergeben
  Control2Harpoon("ControlDown");

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlDownDouble()
{
  // Steuerung an Harpune weitergeben
  //Control2Harpoon("ControlDownDouble");

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlThrow()
{
  // Schlagen beim Nahkampf
  if (GetAction() == "Fight")
  {
    SetAction("Punch");
    return true;
  }
  // Bei vorherigem Doppel-Stop nur Ablegen
  if (GetPlrDownDouble(GetOwner())) return false;

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlThrow")) return true;

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlThrowDouble()
{
  ControlThrow();
  return true;
}

protected func ControlDig()
{
  // Kicken beim Nahkampf
  if (GetAction() == "Fight")
  {
    SetAction("Kick");
    return true;
  }
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlDig")) return true;

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlDigSingle()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlDigSingle")) return true;

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlDigDouble()
{
  if (WildcardMatch(GetAction(), "*Walk")) return false;
  if (WildcardMatch(GetAction(), "*Swim")) return false;
  if (GetAction() == "Dig")                return false;
  if (GetAction() == "Push")               return false;
  if (GetAction() == "Kick")               return false;

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("Activate")) return true;

  // Keine überladene Steuerung
  return _inherited(...);
}

func ControlSpecial()
{
    // ggf. Pistole wegstecken
    if (FindContents(PT7A))
    {
        Holster();
        return false;
    }
    
    // counter for special2 combo
    if(ContentsCount() == 1)
    {
        ctrlSpclCmboCnt = FrameCounter();
        return false;
    }
    
    // Inventar verschieben
    ShiftContents(0, 0, 0, 1);

    // Bewaffnung prüfen
    CheckArmed();
    
    return true;
}

protected func ControlSpecialDouble()
{
  ControlSpecial();
  return true;
}

protected func ControlSpecial2()
{
  // ggf. Pisole ziehen
  if(ctrlSpclCmboCnt > FrameCounter() - 20)
  {
    Holster();
    return false;
  }

  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlSpecial2"))
  {
    Sound("SF_Mode");
    return true;
  }
  // bei angefassten Objekten Holen ermöglichen
  if (GetAction() == "Push")
  {
    var stuff = GetActionTarget();
    if (GetDefCoreVal("GrabPutGet", "DefCore", GetID(stuff)) > 1)
    {
      SetCommand(0, "Get", GetActionTarget(), 0, 0, 0, 1);
      return true;
    }
  }
  Holster();
  return false;
}

protected func ControlSpecial2Double()
{
  ControlSpecial2();
  return true;
}

protected func ControlShoot()
{
  // Steuerung an Inhaltsobjekt weitergeben
  if (Control2Contents("ControlShoot", ...)) return true;

  // Keine überladene Steuerung
  return _inherited(...);
}

protected func ControlCursorLeft()
{
  ControlShoot(ShootingAxis_Upwards);
  return true;
}

protected func ControlCursorMiddle()
{
  var owner = GetOwner();
  DT_CursorChange_LastCursors[owner] = CycleCursor(owner, false, this);
  return DT_CursorChange_NoTouch;
}

protected func ControlCursorRight()
{
  ControlShoot(ShootingAxis_Downwards);
  return true;
}

private func Control2Contents(string command)
{
  // angefasste Objekte haben Vorrang, außer bei Modus-Auswahl
  if ((GetAction() == "Push") && (command != "ControlSpecial2")) return false;

  var result = ObjectCall(Contents(), command, this, ...);
  return result;
}

private func Control2Harpoon(string command)
{
  var harpoon = FindObject2(Find_Container(this), Find_ID(HP7A), Find_Action("Reel"));
  if (harpoon) LocalN("ropeCommand", harpoon) = command;
}

protected func ContactLeft()
{
  // nicht weiter bei Kontakt am Spielfeldrand
  if (!GetContact(0, -1, CNAT_Left)) return false;

  FallDamage();
  return _inherited(...);
}

protected func ContactRight()
{
  // nicht weiter bei Kontakt am Spielfeldrand
  if (!GetContact(0, -1, CNAT_Right)) return false;

  FallDamage();
  return _inherited(...);
}

protected func ContactTop()
{
  FallDamage();
  return _inherited(...);
}

protected func ContactBottom()
{
  FallDamage();
  return _inherited(...);
}

private func FallDamage()
{
  // weiter nur wenn der Clonk noch lebt
  if(!GetAlive()) return false;

  var speed = Max(Abs(GetXDir()), Abs(GetYDir()));

  if (speed >= 70)
  {
    DoEnergy((70 - speed) * 2);
    Sound("Hurt*");
  }
  return true;
}

private func CheckArmed()
{
  var weapon = Contents();
  ScrollHud(LocalN("mode", weapon));
  var ammoPercent = weapon && weapon->~GetAmmoPercent();
  SetAmmoBar(ammoPercent);

  var weaponAction = (weapon && weapon->~IsWeapon() && weapon->~ActionString()) || "";
  var action = GetAction();

  // With a weapon change Dive into Jump
  if(action == "Dive" && weaponAction != "")
  {
    action = "Jump";
  }

  for(var checkAction in ["Walk", "Jump", "Swim"])
  {
    if(WildcardMatch(action, Format("*%s", checkAction)))
    {
      var newAction = Format("%s%s", weaponAction, checkAction);
      if(newAction != action)
      {
        SetActionSmooth(newAction);
      }
      return;
    }
  }
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
  return true;
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
  return true;
}

private func Kicking()
{
  if (!Random(3)) Sound("Kime*");

  DoEnergy(-10, GetActionTarget());
  Fling(GetActionTarget(), 4 * GetDir() - 2, -1);
  SetComDir(COMD_Stop);
  Sound("Punch*");
  return true;
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
  return true;
}

private func Building()
{
  if (GetAction() == "Build")
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
  return true;
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
  if (FindContents(PT7A)) return Exit(pistol);

  if (!pistol)
  {
    pistol = CreateContents(PT7A);
    pistol->SetAmmoPercent(100);
  }
  else
  {
    Enter(this, pistol);
  }
  ShiftContents(0, true, PT7A);
  CheckArmed();
  Sound("SF_Holster");
  return true;
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

  var ammo = pistol->GetAmmoPercent();
  if (ammo == 100) return;

  var cashNeed = (100 - ammo) / 20;
  var cashHave = GetWealth(baseOwner);

  var ammoNeed = 100 - ammo;
  var ammoHave = cashHave * 20;

  ammo += Min(ammoNeed, ammoHave);
  pistol->SetAmmoPercent(ammo);
  if (Contained(pistol) == this) SetAmmoBar(ammo);

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
  if (ContentsCount() >= 5) return true;
  return (0);
}

protected func Collection2(stuff)
{
  if (GetCategory(stuff) & C4D_Object && ContentsCount(GetID(stuff)) == 1)
  {
    // hinten an die Inventarliste hängen
    if (GetID(stuff) != PT7A) ShiftContents();
  }
  // Bewaffnung prüfen
  CheckArmed();
  return true;
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
  return true;
}

protected func Death()
{
  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this, GetKiller());

  // Der Broadcast könnte seltsame Dinge gemacht haben: Clonk ist noch tot?
  if (GetAlive()) return false;

  Sound("SF_Die");
  DeathAnnounce();

  // Letztes Mannschaftsmitglied tot?
  if (!GetCrew(GetOwner())) GameCallEx("RelaunchPlayer", GetOwner(), this);

  // Tod dem Spiel(ziel) berichten
  GameCallEx("ReportHomicide", GetKiller(), GetOwner(), GetID(this));
  return _inherited(...);
}