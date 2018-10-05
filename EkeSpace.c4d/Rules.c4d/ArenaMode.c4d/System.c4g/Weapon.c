#strict 2
#appendto WP7A

/*------------------------------------*\
    Ammo Regeneration
\*------------------------------------*/
func Initialize()
{
  DeactivateWeapon();
  return _inherited(...);
}
func FxAmmoRegenTimer()
{
  AddAmmo(2);
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