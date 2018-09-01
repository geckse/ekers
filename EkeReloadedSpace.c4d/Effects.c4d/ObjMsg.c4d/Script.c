/*-- Messages --*/

// script v1.4 by miniwipf
#strict 2


/* GLOBAL */

global func CastSettleMsg(string nszMsg, object npObj, int ndwClr, bool nfDown, bool nfast)
{
  return (CastMsg(nszMsg,npObj,ndwClr,nfDown,nfast));
}
global func CastMsg(string szMsg, object pObj, int dwClr, bool fDown, bool fast)
{
  if (!pObj &&  this) pObj = this;
  if (!dwClr) dwClr = 0xffffff; // Meistens so gemeint
  // Instanz erstellen
  var obj = CreateContents(_MSG, pObj);
  // Richtung setzen
  if (!fDown) {
    obj -> SetComDir(COMD_Up);
    obj -> SetAction("Up");
  }
  else {
    obj -> SetComDir(COMD_Down);
    obj -> SetAction("Down");
  }
  //obj -> Exit(,,,, Sin(angle, 4), -Cos(angle, 2));
  obj -> Exit(,,,,, -3);
  // Text-FadeOut
  if(!fast){ AddEffect("FadingText", obj, 50, 10, obj,, szMsg, dwClr); }
  else { AddEffect("FadingText", obj, 25, 5, obj,, szMsg, dwClr); }

  return 1;
}

// Effekte

public func FxFadingTextStart(object pTarget, int iNr, int iTemp, string szString, int dwClr)
{
  if (iTemp) return;
  EffectVar(0, pTarget, iNr) = szString;
  EffectVar(1, pTarget, iNr) = dwClr;
  EffectCall(pTarget, iNr, "Show", 0);
  return 1;
}

public func FxFadingTextTimer(object pTarget, int iNr, int iTime)
{
  return EffectCall(pTarget, iNr, "Show", iTime);
}

public func FxFadingTextStop(object pTarget, int iNr, int iReason, bool fTemp)
{
  if (fTemp || iReason) return;
  // Objekt löschen
  return RemoveObject(pTarget);
}

public func FxFadingTextShow(object pTarget, int iNr, int iTime)
{
  // Text anzeigen
  var a = BoundBy(255-(iTime/2)*8, 0, 255);
  if (!a) return -1;
  var clr = SetRGBaValue(EffectVar(1, pTarget, iNr), a);
  return Message("@<c %x>%s</c>", pTarget, clr, EffectVar(0, pTarget, iNr));
}