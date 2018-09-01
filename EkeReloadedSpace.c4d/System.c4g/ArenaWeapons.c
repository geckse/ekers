/*-- Neues Script --*/

#strict 2
#appendto SF5B

public func RejectCollect(id idObject, object pObject)
{
 var other = FindObject2(Find_ID(idObject),Find_Container(this));
 if(other && FindObject(ARWE) && LocalN("ammo",pObject)){
   LocalN("ammo",other) = LocalN("ammo",other)+LocalN("ammo",pObject);
   if(LocalN("ammo",other) >= 100) LocalN("ammo",other) = 100;

   if(idObject == AR5B && LocalN("gGrenades",pObject)){
      LocalN("gGrenades",other) = LocalN("gGrenades",other)+LocalN("gGrenades",pObject);
      if(LocalN("gGrenades",other) >= 100) LocalN("gGrenades",other) = 100;
   }
   pObject->~CastParticles("PxSpark",RandomX(4,12),RandomX(12,20),0,0,RandomX(30,60),60,RGBa(255,255,255),RGBa(225,225,255));
   RemoveObject(pObject);
 }

 return _inherited(idObject,pObject);
}