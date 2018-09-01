/*-- Funktionen --*/

#strict

// Filtert den ClanTag aus dem Spielernamen heraus (Funktioniert natürlich nicht immer)
// Jetzt hab ich Funktion zumindest nicht umsonst geschrieben :)
global func FilterClanTag(string szName, int iRetries) {
  // Versuche bis die Schleife abgebrochen wird
  if(!iRetries) iRetries = 20;
  
  // Filterung des ClanTags zwischen
  if(GetChar(szName, 0) == 91  ||  // [ ( 91)
     GetChar(szName, 0) == 60  ||  // < ( 60)
     GetChar(szName, 0) == 123 ||  // { (123)
     GetChar(szName, 0) == 40) {   // ( ( 40) 
    // Endzeichen suchen des Clantags
    for(var i = 1; i <= iRetries; i++)
      if((GetChar(szName, i) == 93  && GetChar(szName, 0) ==  91) || // ] ( 93)
         (GetChar(szName, i) == 62  && GetChar(szName, 0) ==  60) || // > ( 62)
         (GetChar(szName, i) == 125 && GetChar(szName, 0) == 123) || // } (125)
         (GetChar(szName, i) == 41  && GetChar(szName, 0) ==  40)) { // ) ( 41)
        // Gefilteter Name ohne ClanTag
        var szFilteredName;
        // Baut den Namen ohne ClanTag zusammen
        for(var i = i+1; i <= GetLength(szName); i++)
          if(!szFilteredName) {
            // Wenn da noch ein Leerzeichen ist: Entfernen
            if(GetChar(szName, i) != 32)
              // Zuerst ohne szFilteredName sonst (null)...
              szFilteredName = Format("%c", GetChar(szName, i));
            }
          else
            // ...dann szFilteredName vorranhängen und danach der Buchstabe...
            szFilteredName = Format("%s%c", szFilteredName, GetChar(szName, i));
        // Gibt den Namen ohne ClanTag zurück
        return(szFilteredName);
        }
      return(szName);
    }
  else
    return(szName);
}

global func EliminateTeam(int iTeam) {
  for(var i,j=GetPlayerCount(); j; ++i)
    if(GetPlayerName(i)){
      if(GetPlayerTeam(i) == iTeam) EliminatePlayer(i);
      --j;
      }
}

global func GetPlayerByID(int iPlrID) {
  for(var i = 0; i < GetPlayerCount(); i++) {
    var iPlr = GetPlayerByIndex(i);
    if(GetPlayerID(iPlr) == iPlrID) return iPlr;
  }
  return -1;
}

// Gibt jedem Spieler eines bestimmten Teams eine bestimmte Menge an Geld
global func DoWealthTeam(int iTeam, int iWealth) {
  for(var i, j = GetPlayerCount(); j; ++i) {
    if(GetPlayerName(i)) {
      if(GetPlayerTeam(i) == iTeam) 
        DoWealth(i, iWealth);
      --j;
    }
  }
}

global func TeamSound(string szSound, bool fGlobal, object pObj, int iVolume, int iTeam, int iLoopCount) {
  for(var i, j = GetPlayerCount(); j; ++i) {
    if(GetPlayerName(i)) {
      if(GetPlayerTeam(i) == iTeam) {
        Sound(szSound, fGlobal, pObj, iVolume, i + 1, iLoopCount);
      }
      --j;
    }
  }
}

global func FlyingMessage(string szMessage, object pObj, int iPlr, int iOffX, int iOffY, int dwColor, int iSpeed, int iFadeTime) {
  var pTarget = CreateObject(DUMY, iOffX, iOffY); //, GetX(pObj), GetY(pObj));
  AddEffect("FlyingMessage", pTarget, 1, 1, 0, 0, [szMessage, iPlr, iOffX, iOffY, dwColor, iSpeed, iFadeTime]);
}

global func FxFlyingMessageStart(object pTarget, int iEffectNumber, int iTemp, var1, var2, var3, var4) {
  EffectVar(0, pTarget, iEffectNumber) = var1[0]; // szMessage
  EffectVar(1, pTarget, iEffectNumber) = var1[1]; // iPlr
  EffectVar(2, pTarget, iEffectNumber) = var1[2]; // iXOff
  EffectVar(3, pTarget, iEffectNumber) = var1[3]; // iYOff
  EffectVar(4, pTarget, iEffectNumber) = var1[4]; // dwColor
  EffectVar(5, pTarget, iEffectNumber) = var1[5]; // iSpeed
  EffectVar(6, pTarget, iEffectNumber) = var1[6]; // iFadeTime
}

global func FxFlyingMessageTimer(object pTarget, int iEffectNumber, int iEffectTime) {
  var szMessage = EffectVar(0, pTarget, iEffectNumber);
  var iPlr = EffectVar(1, pTarget, iEffectNumber);
  var iOffX = EffectVar(2, pTarget, iEffectNumber);
  var iOffY = EffectVar(3, pTarget, iEffectNumber);
  var iSpeed = EffectVar(5, pTarget, iEffectNumber);
  var iFadeTime = EffectVar(6, pTarget, iEffectNumber);
  var dwColor = SetRGBaValue(EffectVar(4, pTarget, iEffectNumber), 255 * iEffectTime / iFadeTime, 0);
  
  // Entfernen sobald komplett ausgefadet
  if((255 * iEffectTime / iFadeTime) >= 255) {
    RemoveObject(pTarget);
    return -1;
  }
  
  CustomMessage(szMessage, pTarget, iPlr, iOffX, iOffY - (iEffectTime / iSpeed), dwColor);
  return 0;
}

global func FadeOut(int iFadeTime, int iDelay, object pObj) {
  AddEffect("FadeObject", pObj, 1, 1, 0, 0, iFadeTime, iDelay);
}

global func FxFadeObjectStart(object pTarget, int iEffectNumber, int iTemp, int iFadeTime, int iDelay) {
  EffectVar(0, pTarget, iEffectNumber) = iFadeTime;
  EffectVar(1, pTarget, iEffectNumber) = iDelay;
}

global func FxFadeObjectTimer(object pTarget, int iEffectNumber, int iEffectTime) {
  var iFadeTime = EffectVar(0, pTarget, iEffectNumber);
  var iDelay = EffectVar(1, pTarget, iEffectNumber);
  
  if(iEffectTime < iDelay) return 0;
  
  if((255 * (iEffectTime - iDelay) / iFadeTime) >= 255) {
    RemoveObject(pTarget);
    return -1;
  }
  
  SetObjAlpha(255 * (iEffectTime - iDelay) / iFadeTime, pTarget);
  //var dwColor = SetRGBaValue(GetClrModulation(pTarget), 255 * (iEffectTime - iDelay) / iFadeTime, 0);
  //SetClrModulation(dwColor, pTarget);
  return 0;
}

global func SetObjAlpha(int byAlpha, object pObj) {
  var dwClrMod = GetClrModulation(pObj);
  if(!dwClrMod) dwClrMod = RGB(255, 255, 255);
  if(!dwClrMod) dwClrMod = byAlpha << 24; 
    else dwClrMod = dwClrMod & 16777215 | byAlpha << 24;
  return SetClrModulation(dwClrMod, pObj);
}

global func DrawMaterialBlock(string szMaterial, int iX, int iY, bool fSub) {
  DrawMaterialQuad(szMaterial, iX, iY+1, iX+10, iY+1, iX+10, iY+11, iX, iY+11, fSub);
}
