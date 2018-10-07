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
  if(GetAmmoPercent() == 100) ActivateWeapon();
}
func ActivateWeapon()
{
  if(arenaModeRule) RemoveEffect("AmmoRegen",this);
  return _inherited(...);
}
func DeactivateWeapon()
{
  if(arenaModeRule) AddEffect("AmmoRegen", this, 1, 2, this);
  return _inherited(...);
}