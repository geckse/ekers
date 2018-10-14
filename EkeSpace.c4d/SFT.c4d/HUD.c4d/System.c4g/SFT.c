/*-- HUD --*/

#strict 2
#appendto SF7A

local itemMode;
local lifeBar;
local ammoBar;
local fuelBar;
local hudMount;
local maxFuel;
local killHudFx;

func Recruitment()
{
    maxFuel = this->MaxFuel();
    AddEffect("Hud", this, 21, 0, this);
    return _inherited(...);
}

func CrewSelection(deselect)
{
    if(!deselect)
    {
        if(!Contained(this)) ShowHud();
    }
    if(deselect) {
        HideHud();
    }
    return _inherited(deselect, ...);
}

func Entrance() {
    var container = Contained(this);
    if(container && hudMount) {
        hudMount -> SetAction("Attach", container);
        HideHud();
    }
    return _inherited(...);
}
func Departure() {
    EnsureHud();
    hudMount -> SetAction("Attach", this);
    ScrollHud(LocalN("mode", Contents()), true);
    var owner = GetOwner(this);
    if(GetCursor(owner) == this) ScheduleCall(0, "ShowHud", 2);
    return _inherited(...);
}

func Death()
{
    HideHud();
    RemoveEffect("Hud", this);
    return _inherited(...);
}

// find HUD components, create if needed
func CreateHud()
{
    var owner = GetOwner(this);

    if(!hudMount) hudMount = CreateObject(HM7A,0,0,owner);
    hudMount->SetObjectLayer(hudMount);
    if(!itemMode) {
        itemMode = CreateObject(IM7A,0,0,owner);
        SetObjDrawTransform(667,0,0,0,667,0,itemMode);
        itemMode->SetObjectLayer(hudMount);
    }

    if(!lifeBar) {
        lifeBar = CreateObject(EB7A,0,0,owner);
        SetClrModulation(RGBa(202,119,119,0), lifeBar);
        SetGraphics("Overlay", lifeBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
        lifeBar->SetObjectLayer(hudMount);
    }
    if(!ammoBar) {
        ammoBar = CreateObject(EB7A,0,0,owner);
        SetClrModulation(RGBa(202,202,202,0), ammoBar);
        SetGraphics("Overlay", ammoBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
        ammoBar->SetObjectLayer(hudMount);
    }
    if(!fuelBar) {
        fuelBar = CreateObject(EB7A,0,0,owner);
        SetClrModulation(RGBa(119,202,146,0), fuelBar);
        SetGraphics("Overlay", fuelBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
        fuelBar->SetObjectLayer(hudMount);
    }

    MoveHud();

    var obj = Contents();
    ScrollHud(LocalN("mode", obj), true);
}

// scroll item mode
func ScrollHud(mode, fast)
{
    EnsureHud();
    itemMode -> Scroll(mode, fast);
    return(1);
}

// move HUD to selected clonk
func MoveHud()
{
    var hudOffsetY = 24;
    hudMount -> SetAction("Attach", this);
    itemMode -> SetAction("Attach", hudMount);

    SetVertexXY(0, -8, hudOffsetY + 6,lifeBar);
    lifeBar -> SetAction("Attach", hudMount);

    SetVertexXY(0, -8, hudOffsetY, ammoBar);
    ammoBar -> SetAction("Attach", hudMount);

    SetVertexXY(0, -8, hudOffsetY - 6, fuelBar);
    fuelBar -> SetAction("Attach", hudMount);
}

func EnsureHud()
{
    if(!hudMount) CreateHud();
}

// hide HUD
func HideHud()
{
    EnsureHud();
    SetVisibility(VIS_None, hudMount);
    SetVisibility(VIS_None, itemMode);
    SetVisibility(VIS_None, lifeBar);
    SetVisibility(VIS_None, ammoBar);
    SetVisibility(VIS_None, fuelBar);
}

// show HUD
func ShowHud()
{
    EnsureHud();
    SetVisibility(VIS_Owner | VIS_God, hudMount);
    SetVisibility(VIS_Owner | VIS_God, itemMode);
    SetVisibility(VIS_Owner | VIS_God, lifeBar);
    SetVisibility(VIS_Owner | VIS_God, ammoBar);
    SetVisibility(VIS_Owner | VIS_God, fuelBar);
}

func FxHudStart(object target, int effectNumber, int temp)
{
    if(temp == FX_Call_Normal)
    {
        EnsureHud();
        EffectCall(target, effectNumber, "Damage", 0, FX_Call_DmgScript);
        DoFuel();
        CheckArmed();
    }
}

func FxHudDamage(object target, int effectNumber, int damage, int cause)
{
    EnsureHud();
    var newEnergy = GetObjectVal("Energy") + damage;
    newEnergy = BoundBy(100 * newEnergy / GetPhysical("Energy"), 0, 100);
    SetPhase(newEnergy + 1, lifeBar);
    return damage;
}

func DoFuel()
{
    EnsureHud();
    var ret = _inherited(...);
    // update fuel bar
    var fuel = this->GetFuel();
    var perc = (fuel*100)/maxFuel;
    SetPhase(perc + 1, fuelBar);
    if(perc < 33 && this->IsActive()) Sound("JB_Doum",1,this,100,GetOwner()+1);

    return ret;
}

func SetAmmoBar(int ammo)
{
    EnsureHud();
    SetPhase(ammo, ammoBar);

    return _inherited(ammo, ...);
}

func WeaponActivated()
{
    EnsureHud();
    SetGraphics("Active", hudMount);
    SetClrModulation(RGBa(119,173,202,0), ammoBar);
}

func WeaponDeactivated()
{
    EnsureHud();
    SetGraphics(0, hudMount);
    SetClrModulation(RGBa(202,202,202,0), ammoBar);
}

func CheckArmed()
{
  var weapon = Contents();
  if(!weapon || !weapon->~IsWeapon() || weapon->~IsActive())
  {
    WeaponActivated();
  }
  else
  {
    WeaponDeactivated();
  }

  return _inherited(...);
}