/*-- Extra Lognachrichten --*/

#strict

global func ShowMessage(szString, a,b,c,d,e,f,g,e,h) {
  var obj, i;
  // Alle vorigen Logs speichern und verschieben
  while(obj = FindObject(_LOG, 0-GetX(), 0-GetY(), -1, -1, 0, 0, 0, 0, obj)) Var(i++) = obj;
  while(--i>=0) SetPosition(GetX(Var(i)), GetY(Var(i))-22, Var(i));
  // Neues Log hinzufügen
  var szText = Format(szString, a,b,c,d,e,f,g,e,h);
  obj = CreateObject(_LOG, -GetX(), 250-GetY(), -1);
  AddEffect("Log", obj, 1, 1, 0, _LOG, szText);
  return(1);
}

//global func ShowTeamMessage(szString, iTeam, a, b, c, d, e, f, g, h) {
//  var pObj, i;
//
//}

func FxLogStart(pObj, iNumber, fTmp, szMessage) {
  if(fTmp) return();
  EffectVar(0, pObj, iNumber) = 255*4;
  EffectVar(1, pObj, iNumber) = szMessage;
}

func FxLogTimer(pObj, iNumber)
{
  // Wenn es oben herausgeschoben wird, kommt es unten wieder rein. Sowas suckt.
  if(GetY(pObj) < 0) return -1;
  // Langsam ausfaden
  if(!--EffectVar(0, pObj, iNumber)) return(-1);
  CustomMessage(Format("     %s", EffectVar(1, pObj, iNumber)), pObj, NO_OWNER, 22, 50, RGBa(255,255,255,Max(255-EffectVar(0, pObj, iNumber)/4)), 0, 0, MSG_NoLinebreak);
}

func FxLogStop(pObj, iNumber, iReason, fTmp) {
  if(fTmp) return();
  RemoveObject(pObj);
}