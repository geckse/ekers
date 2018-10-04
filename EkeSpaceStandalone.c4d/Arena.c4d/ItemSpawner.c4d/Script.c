/*-- Spawnpoint --*/

#strict

local initialized, angle, player, spawntimer;

global func PlaceSpawnpoint(id idObj, int iX, int iY, int timer)
{
  var spwn = CreateObject(SPNP, iX, iY, -1);
  spwn->CreateContents(idObj);
  if(timer)
    spwn->LocalN("spawntimer") = timer;
  return(spwn);
}

protected func Initialize()
{
  // Standardtimer = 1000 Frames
  spawntimer = 1000;
  SetClrModulation(RGBa(0,0,0,255));
}

protected func Timer()
{
   // Objekt als Layer auflegen
  SetGraphics(0, 0, GetID(Contents()), 1, 1);

  // Noch nicht initialisiert?
  if(!initialized)
    // Ein Inhaltsobjekt?
    if(Contents())
      // Initialisieren
      return(Initialized());
  // Kein Inhalt?
  if(!Contents())
    {
    // Nicht mehr initialisiert
    initialized = false;
    return();
    }
  // Tolle Effekt starten
  angle += 10;
  if(angle >= 360) angle = 0;
  SetObjDrawTransform(1000, 0,0,0, 1000, Sin(angle, 8)*1000 - 2000,0, 1);
  if(Random(2)) CreateParticle("VMSpark", RandomX(-5,5), RandomX(5,10), 0, -5, 25, RGBa(255, 255, 255, 100));
  // Alle Timer runterzählen
  DecreaseTimer();
}

private func Initialized()
{
  // Unsichtbar werden
  SetAction("Invis");
  // Objekt als Layer auflegen
  SetGraphics(0, 0, GetID(Contents()), 1, 1);
  // Transformation
  SetObjDrawTransform(1000, 0,0,0, 1000, -5000,0, 1);
  // Sammeleffekt starten
//  AddEffect("Collect", this(), 1, 3, this());
  // Objekt(e) erzeugen
  // Waffen-Bleiben-Regel
  if(FindObject(WPST))
    {
    for(var i=0 ; i < GetPlayerCount() ; i++)
      Local() += 2**GetPlayerByIndex(i);
    SetVisibility(VIS_Local() | VIS_God());
    }
  else
    Local() = true;
  player = CreateArray();
  // Initialisiert
  initialized = true;
}

/* Timer runterzählen */

private func DecreaseTimer()
{
  // Waffen-Bleiben-Regel
  if(FindObject(WPST))
    {
    for(var i=0 ; i < GetPlayerCount() ; i++)
      // Spielertimer runterzählen
      {
      if(player[GetPlayerByIndex(i)])
        player[GetPlayerByIndex(i)] -= 5;
      if(player[GetPlayerByIndex(i)] <= 0 && !(Local() & 2**GetPlayerByIndex(i)))
        {
        // Spieler kann das Objekt wieder einsammeln
        player[GetPlayerByIndex(i)] = 0;
        Local() += 2**GetPlayerByIndex(i);
        }
      }
    }
  else
    {
    // Timer runterzählen
    player[0] -= 5;
    if(player[0] <= 0)
      {
      // Objekt ist wieder da
      player[0] = 0;
      Local() = true;
      SetVisibility(VIS_All());
      }
    }
}

/* Einsammel-Effekte */
/*
public func FxCollectTimer()
{
  // Ist ein Clonk hier? -> Einsammeln lassen
  var pObj;
  for(var pClonk in FindObjects(Find_AtPoint(), Find_OCF(OCF_CrewMember()), Find_OCF(OCF_CrewMember()), Find_NoContainer()))
    if(CheckCollect(GetOwner(pClonk)))
      {
      pObj = CreateContents(GetID(Contents()));
      // Kann der Clonk einsammeln?
      Collect(pObj, pClonk);
      if(Contained(pObj) == this()) RemoveObject(pObj);
      else
        {
        Sound("Grab", 0, pClonk, 0, GetOwner(pClonk)+1);
        Collected(GetOwner(pClonk));
        // Munition
        if(pObj->~IsAmmoPacket())
          pObj->~TransferAmmo(pClonk);
        }
    }
}*/

public func RejectEntrance(object pClonk)
{
  // Objekt ist ein Clonk?
  if(!(GetOCF(pClonk) & OCF_CrewMember) && !(pClonk->~CanCollectFromSpawnpoints())) return(1);
  // Ich hab Contents?
  if(!Contents()) return(1);
  // Darf einsammeln
  if(CheckCollect(GetOwner(pClonk)))
  {
    var pObj = CreateContents(GetID(Contents()));
    // Kann der Clonk einsammeln?
    var tid = GetID(Contents());
    if(tid == AR7A || tid == UZ7A || tid == SG7A || tid == FT7A || tid == IT7A || tid == RL7A){
       pObj->~SetAmmoPercent(50, WP7A_All);
       if(tid == RL7A){
           pObj->LocalN("ammo") = 100;
           Enter(pObj, CreateObject(MS7A,0,0,GetOwner(pClonk)));
         }
    }
    SetOwner(GetOwner(pClonk),pObj);
    if((pClonk->~RejectCollect(GetID(pObj), pObj) || !Collect(pObj, pClonk) || Contained(pObj) == this()) && pObj) {
      RemoveObject(pObj);
    } else {
      Sound("Grab", 0, pClonk, 0, GetOwner(pClonk)+1);
      Collected(GetOwner(pClonk));
    }
  }
  return(1);
}

private func CheckCollect(int iPlr) // Überprüft, ob ein Spieler das Objekt einsammeln darf
{
  // Waffen-Bleiben-Regel
  if(FindObject(WPST))
    return(Local() & 2**iPlr);
  else
    return(Local());
}

private func Collected(int iPlr) // Regelt, dass ein Spieler das Objekt einsammelt
{
  // Waffen-Bleiben-Regel
  if(FindObject(WPST))
    {
    // Spielertimer hochsetzen
    player[iPlr] = spawntimer;
    // Nicht mehr sichtbar für den Spieler
    Local() -= 2**iPlr;
    }
  else
    {
    // Timer hochsetzen
    player[0] = spawntimer;
    // Nicht mehr einsammelbar
    Local() = false;
    // Nicht mehr sichtbar
    SetVisibility(VIS_God());
    }
}