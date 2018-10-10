#strict 2

local transformAdjust;

func Initialize()
{
  transformAdjust = 15 * 1000 * 6/10;
  SetGraphics(0, this, AC7A, GFX_Overlay, GFXOV_MODE_Picture);
  SetObjDrawTransform(400,0,transformAdjust, 0,400,transformAdjust, this, GFX_Overlay);
  
  AddEffect("AmmoCircle", this, 1, 2, this);
  
  return _inherited(...);
}

func FxAmmoCircleTimer()
{
  var ammo = this->GetAmmoPercent() * 2 / 10;
  if(ammo) ammo = Format("%d", ammo);
  SetGraphics(ammo, this, AC7A, GFX_Overlay, GFXOV_MODE_Picture);
  if(IsActive()) {
    SetClrModulation (RGBa(119,173,202,0), this, GFX_Overlay);
  }
  else {
    SetClrModulation (RGBa(255,255,255,0), this, GFX_Overlay);
  } 
}