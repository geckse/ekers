/*-- Energy Shield --*/

#strict 2
#appendto SF7A

func PreRegenerateNoDamageTime() { return 180; }
func RegenerateAmount() { return 1000; }

local maxShieldEnergy;
local shieldEnergy;

func Initialize()
{
    maxShieldEnergy = 150000;
    DoShieldEnergy(maxShieldEnergy);
    AddEffect("EnergyShield", this, 20, 10, this);
    return _inherited(...);
}

// EffectVar 0 contains the effectTime of the last damage

func FxEnergyShieldDamage(object target, int effectNumber, int damage, int cause)
{
    // no damage or healing is ok
    if(damage >= 0)
    {
        return damage;
    }

    DoShieldEnergy(damage); // damage is negative value

    // disable regeneration temporarily
    EffectVar(0, target, effectNumber) = 0;

    if(shieldEnergy < 1)
    {
      return damage;
    }
    return 0;
}

func FxEnergyShieldTimer(object target, int effectNumber, int effectTime)
{
    if(!EffectVar(0, target, effectNumber))
    {
        EffectVar(0, target, effectNumber) = effectTime;
    }

    if(EffectVar(0, target, effectNumber) + PreRegenerateNoDamageTime() <= effectTime)
    {
        DoShieldEnergy(RegenerateAmount());
    }
}

func DoShieldEnergy(int amount)
{
    return shieldEnergy = BoundBy(shieldEnergy + amount, 0, maxShieldEnergy);
}

func GetShieldEnergy()
{
  return shieldEnergy;
}