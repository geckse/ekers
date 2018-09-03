/*-- Neues Script --*/

#strict 2
#appendto SF5B

public func RejectCollect(id idObject, object pObject) {
    var other = FindObject2(Find_ID(idObject), Find_Container(this));
    if (other && FindObject(ARWE)) {
		
		// move ammo in other object
		if (LocalN("ammo", pObject)) {
			LocalN("ammo", other) = LocalN("ammo", other) + LocalN("ammo", pObject);
			if (LocalN("ammo", other) >= 100) LocalN("ammo", other) = 100;

			if (idObject == AR5B && LocalN("gGrenades", pObject)) {
				LocalN("gGrenades", other) = LocalN("gGrenades", other) + LocalN("gGrenades", pObject);
				if (LocalN("gGrenades", other) >= 100) LocalN("gGrenades", other) = 100;
			}
		}
        //  move missile in other rocket launcher
        if (idObject == RL5B) {
            if (FindContents(MS5B, pObject) && (ContentsCount(MS5B, other) == 0)) {
                CreateContents(MS5B, other);
                LocalN("ammo", other) = 100;
            }
        }
		
		// remove duplicate and cast particles
        pObject->~CastParticles("PxSpark", RandomX(4, 12), RandomX(12, 20), 0, 0, RandomX(30, 60), 60, RGBa(255, 255, 255), RGBa(225, 225, 255));
        RemoveObject(pObject);
    }
    return _inherited(idObject, pObject);
}