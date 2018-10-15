/*-- Energy Shield --*/

#strict 2
#appendto SF7A

func PreRegenerateNoDamageTime() { return 250; }
func RegenerateAmount() { return 3500; }

local maxShieldEnergy;
local shieldEnergy;
local cone;

func Initialize()
{
    maxShieldEnergy = 25000;
    DoShieldEnergy(maxShieldEnergy);
    AddEffect("EnergyShield", this, 20, 10, this);
    
    // energy cone
    var owner = GetOwner();
    cone = CreateObject(EC7A,0,0,owner);
    SetVisibility(VIS_None, cone);
    cone -> SetAction("Attach", this);
    
    return _inherited(...);
}

// EffectVar 0 contains the effectTime of the last damage

func FxEnergyShieldDamage(object target, int effectNumber, int damage, int cause)
{
    // no damage or healing is ok
    if(damage >= 0)
    {
        // hide cone
        SetVisibility(VIS_None, cone);
        
        // return damage
        return damage;
    }

    DoShieldEnergy(damage); // damage is negative value

    // disable regeneration temporarily
    EffectVar(0, target, effectNumber) = 0;
    
    // show cone
    // SetVisibility(VIS_All, cone);

    if(shieldEnergy < 1)
    {
        // hide cone
        SetVisibility(VIS_None, cone);
        
        // return damage
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
        // hide cone
        SetVisibility(VIS_None, cone);
        
        // regen shield
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