#strict 2
#appendto SF7A

/*------------------------------------------*\
    Remove Weapon Duplicates On Collect
\*------------------------------------------*/
public func RejectCollect(id idObject, object pObject) {
	if (arenaModeRule && pObject->~IsWeapon())
    {
        var other = FindObject2(Find_ID(idObject), Find_Container(this));
        if(other)
        {
            // add ammo
            var ammo1 = pObject->GetAmmo(1);
            var ammo2 = other->GetAmmo(1);
            var totalAmmo = ammo1 + ammo2;
            if(totalAmmo < 500) totalAmmo = 500;
            other->SetAmmo(totalAmmo, 1);
            
            // add grenades
            if(idObject == AR7A)
            {
                var ammo1 = pObject->GetAmmo(2);
                var ammo2 = other->GetAmmo(2);
                var totalAmmo = ammo1 + ammo2;
                if(totalAmmo < 500) totalAmmo = 500;
                other->SetAmmo(totalAmmo, 2);
            }
            
            // remove duplicate
            pObject->~CastParticles("PxSpark", RandomX(4, 12), RandomX(12, 20), 0, 0, RandomX(30, 60), 60, RGBa(255, 255, 255), RGBa(225, 225, 255));
            RemoveObject(pObject);
            CheckArmed();
            return false;
        }
    }
    return _inherited(...);
}

/*------------------------------------------*\
    Prevent Collection Of Objects
\*------------------------------------------*/
func RejectCollect(id idObject, object pObject)
{
    if(arenaModeRule)
    {
        if(idObject == ROCK || idObject == SL7A) return 1;
    }
    return _inherited(idObject, pObject);
}