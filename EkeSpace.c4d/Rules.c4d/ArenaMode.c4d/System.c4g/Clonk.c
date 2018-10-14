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
            var ammo = pObject->GetAmmo();
            if(ammo < 250) ammo = 250;
            other->AddAmmo(ammo);
            
            // remove duplicate
            pObject->~CastParticles("PxSpark", RandomX(4, 12), RandomX(12, 20), 0, 0, RandomX(30, 60), 60, RGBa(255, 255, 255), RGBa(225, 225, 255));
            RemoveObject(pObject);
            CheckArmed();
            return false;
        }
    }
    return _inherited(idObject, pObject);
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