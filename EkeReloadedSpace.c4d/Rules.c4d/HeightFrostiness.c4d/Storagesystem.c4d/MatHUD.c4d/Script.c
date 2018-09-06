/*-- Neues Objekt --*/

#strict

local sMat;

protected func Initialize()
{
    SetPosition(-140,14);        // Positionieren
    Local(0)=Local(1)=0;        // Parallax auf 0 Setzen
    SetCategory(60817409);   // Parallax+Object+FoWIgnore
    SetVisibility(VIS_Owner());   // Nur für den Besitzer sichtbar
}
public func Set(int iOwner, datMat, int xversatz){
sMat = datMat;
SetGraphics(datMat);
SetOwner(iOwner);
SetPosition(-140-xversatz,14);
}

protected func HudCount()
{
  var obj, iCount;
  while(obj = FindObjectOwner(GetID(), GetOwner(),0, 0, 0, 0, 0, 0, 0, obj))
  {
    if(obj==this()) continue;
    iCount++;
  }
  return(iCount);
}

public func Check(){
 if(GetOwner()==-1) return(RemoveObject());
 var stri = "";
 stri = Format("%d",GetMat(GetOwner(),sMat));
 CustomMessage (stri, this(), GetOwner(), 0, +43);

}