/*-- HUD --*/

#strict 2

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
    AddEffect("Hud", this, 1, 2, this);
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
    return _inherited(...);
}

func Entrance() {
    var container = Contained(this);
    if(container && hudMount) {
        hudMount -> SetAction("Attach", container);
        itemMode -> SetAction("Attach", container);
        lifeBar -> SetAction("Attach", container);
        ammoBar -> SetAction("Attach", container);
        fuelBar -> SetAction("Attach", container);
        HideHud();
    }
    return _inherited(...);
}
func Departure() {
    if(!hudMount) CreateHud();
    hudMount -> SetAction("Attach", this);
    itemMode -> SetAction("Attach", this);
    lifeBar -> SetAction("Attach", this);
    ammoBar -> SetAction("Attach", this);
    fuelBar -> SetAction("Attach", this);
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
    if(!itemMode) {
        itemMode = CreateObject(IM7A,0,0,owner);
        SetObjDrawTransform(667,0,0,0,667,0,itemMode);
    }

    if(!lifeBar) {
        lifeBar = CreateObject(EB7A,0,0,owner);
        SetClrModulation(RGBa(202,119,119,0), lifeBar);
        SetGraphics("Overlay", lifeBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
    }
    if(!ammoBar) {
        ammoBar = CreateObject(EB7A,0,0,owner);
        SetClrModulation(RGBa(202,202,202,0), ammoBar);
        SetGraphics("Overlay", ammoBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
    }
    if(!fuelBar) {
        fuelBar = CreateObject(EB7A,0,0,owner);
        SetClrModulation(RGBa(119,202,146,0), fuelBar);
        SetGraphics("Overlay", fuelBar, EB7A, GFX_Overlay, GFXOV_MODE_Base);
    }

    MoveHud();

    var object = Contents();
    ScrollHud(LocalN("mode", object), true);
}

// scroll item mode
func ScrollHud(mode, fast)
{
    if(!hudMount) CreateHud();
    itemMode -> Scroll(mode, fast);
    return(1);
}

// move HUD to selected clonk
func MoveHud()
{
    var hudX = 0;
    var hudY = 24;

    SetVertexXY(0,hudX,hudY,hudMount);
    hudMount -> SetAction("Attach", this);

    SetVertexXY(0,hudX + 18,hudY,itemMode);
    itemMode -> SetAction("Attach", this);

    SetVertexXY(0,hudX - 8,hudY + 6,lifeBar);
    lifeBar -> SetAction("Attach", this);

    SetVertexXY(0,hudX - 8,hudY,ammoBar);
    ammoBar -> SetAction("Attach", this);

    SetVertexXY(0,hudX - 8,hudY - 6,fuelBar);
    fuelBar -> SetAction("Attach", this);
}

// hide HUD
func HideHud()
{
    if(!hudMount) CreateHud();
    SetVisibility(VIS_None, hudMount);
    SetVisibility(VIS_None, itemMode);
    SetVisibility(VIS_None, lifeBar);
    SetVisibility(VIS_None, ammoBar);
    SetVisibility(VIS_None, fuelBar);
}

// show HUD
func ShowHud()
{
    if(!hudMount) CreateHud();
    SetVisibility(VIS_Owner, hudMount);
    SetVisibility(VIS_Owner, itemMode);
    SetVisibility(VIS_Owner, lifeBar);
    SetVisibility(VIS_Owner, ammoBar);
    SetVisibility(VIS_Owner, fuelBar);
}

func FxHudTimer()
{
    // create hud if needed
    if(!hudMount) CreateHud();

    // update life bar
    SetPhase(GetEnergy() + 1, lifeBar);

    // update ammo bar
    var item = Contents();
    var activeFx = GetEffect("Active", item);
    SetPhase(item && item->~GetAmmoPercent() + 1, ammoBar);
    if (activeFx || GetID(item) == PT7A) {
        SetGraphics("Active", hudMount);
        SetClrModulation(RGBa(119,173,202,0), ammoBar);
    }
    else {
        SetGraphics(0, hudMount);
        SetClrModulation(RGBa(202,202,202,0), ammoBar);
    }

    // update fuel bar
    var fuel = this->GetFuel();
    var perc = (fuel*100)/maxFuel;
    SetPhase(perc + 1, fuelBar);
    if(perc < 33 && this->IsActive()) Sound("JB_Doum",1,this,100,GetOwner()+1);
}