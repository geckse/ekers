/*-- Energy Shield --*/

#strict 2
#appendto SF7A

local maxShieldEnergy;
local shieldEnergy;
local shieldHit;

func Initialize()
{
    maxShieldEnergy = 150000;
    shieldEnergy = maxShieldEnergy;
    AddEffect("EnergyShield", this, 1, 0, this);
    return _inherited(...);
}

func FxEnergyShieldDamage(object target, int effectNumber, int damage, int cause)
{
    var shieldDamage = damage + 1000;
    shieldEnergy = shieldEnergy + shieldDamage; // shieldDamage is negative value
    if(shieldDamage) DebugLog("shieldEnergy: %d", shieldEnergy);
    if(shieldEnergy < 1) {
      shieldEnergy = 0;
      return damage;
    }
    return 0;
}

func GetShieldEnergy() {
  return shieldEnergy;
}