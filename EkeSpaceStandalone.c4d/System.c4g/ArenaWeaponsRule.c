/*-- Arena Weapons --*/

/*
#strict 2
#appendto SF7A

public func RejectCollect(id idObject, object pObject)
{
	var other = FindObject2(Find_ID(idObject), Find_Container(this));
	if (other && FindObject(ARWE))
	{
		if(idObject == AR7A || idObject == SG7A)
		{
			// ammo addition
			LocalN("ammo", other) += LocalN("ammo", pObject);
			if (LocalN("ammo", other) > 100) LocalN("ammo", other) = 100;
			
			// set min ammo
			if (LocalN("ammo", other) < 50) LocalN("ammo", other) = 50;

			// grenades addition
			// LocalN("gGrenades", other) += LocalN("gGrenades", pObject);
			// if (LocalN("gGrenades", other) > 100) LocalN("gGrenades", other) = 100;
			
            // remove duplicate
            pObject->~CastParticles("PxSpark", RandomX(4, 12), RandomX(12, 20), 0, 0, RandomX(30, 60), 60, RGBa(255, 255, 255), RGBa(225, 225, 255));
            RemoveObject(pObject);
            CheckArmed();
			return false;
		}
        else if (idObject == RL7A)
		{
			// rocket addition
            if ((ContentsCount(MS7A, other) == 0))
			{
                CreateContents(MS7A, other);
                LocalN("ammo", other) = 100;
            }
			
            // remove duplicate
            pObject->~CastParticles("PxSpark", RandomX(4, 12), RandomX(12, 20), 0, 0, RandomX(30, 60), 60, RGBa(255, 255, 255), RGBa(225, 225, 255));
            RemoveObject(pObject);
            CheckArmed();
			return false;
        }
	}
	return _inherited(idObject, pObject);
}