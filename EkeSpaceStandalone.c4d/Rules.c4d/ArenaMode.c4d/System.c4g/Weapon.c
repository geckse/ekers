#strict 2
#appendto WP7A

/*------------------------------------*\
    Ammo Regeneration
\*------------------------------------*/
func Initialize()
{
    // arenaModeRule = FindObject2(Find_ID(AM7A));
    arenaModeRule = 1;
    DebugLog("%d", arenaModeRule);
    return _inherited(...);
}
func FxAmmoRegenTimer()
{
  AddAmmo(1);
}
func ActivateWeapon()
{
  if(!arenaModeRule) return _inherited(...);
  RemoveEffect("AmmoRegen",this);
  return _inherited(...);
}
func DeactivateWeapon()
{
  if(!arenaModeRule) return _inherited(...);
  AddEffect("AmmoRegen", this, 1, 2, this);
  return _inherited(...);
}