#strict 2
#appendto SF7A

/*------------------------------------------*\
    Remove Weapon Duplicates On Collect
\*------------------------------------------*/
public func RejectCollect(id idObject, object pObject) {
	var other = FindObject2(Find_ID(idObject), Find_Container(this));
	if (other && FindObject(AM7A)) {
        
        // ammo addition
		if (LocalN("ammo", pObject) || LocalN("ammo", other)) {
			LocalN("ammo", other) += LocalN("ammo", pObject);
			if (LocalN("ammo", other) >= 100) LocalN("ammo", other) = 100;
		}

        // grenades addition
		if (LocalN("gGrenades", pObject) || LocalN("gGrenades", other)) {
			LocalN("gGrenades", other) += LocalN("gGrenades", pObject);
			if (LocalN("gGrenades", other) >= 100) LocalN("gGrenades", other) = 100;
		}

        //  rocket addition
        if (idObject == RL7A) {
            if (FindContents(MS7A, pObject) && (ContentsCount(MS7A, other) == 0)) {
                CreateContents(MS7A, other);
                LocalN("ammo", other) = 100;
            }
        }
        
        // set min ammo and remove duplicate
        if(idObject->IsWeapon()) {
            
            // set min ammo
            if (LocalN("ammo", other) < 50) LocalN("ammo", other) = 50;
            
            // remove duplicate
            pObject->~CastParticles("PxSpark", RandomX(4, 12), RandomX(12, 20), 0, 0, RandomX(30, 60), 60, RGBa(255, 255, 255), RGBa(225, 225, 255));
            RemoveObject(pObject);
            CheckArmed();
            return false;
        }
	}
    // nicht mehr als 5 Objekte tragbar
    if (ContentsCount() >= 5) return(1);
    return (0);
}