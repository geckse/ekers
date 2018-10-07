#strict 2
#appendto WP7A

/*------------------------------------*\
    Ammo Regeneration
\*------------------------------------*/
func FxAmmoRegenTimer()
{
  AddAmmo(2);
  if(GetAmmoPercent() == 100) ActivateWeapon();
}
func Activated()
{
  if(arenaModeRule) RemoveEffect("AmmoRegen",this);
  return _inherited(...);
}
func Deactivated()
{
  if(arenaModeRule) AddEffect("AmmoRegen", this, 1, 2, this);
  return _inherited(...);
}