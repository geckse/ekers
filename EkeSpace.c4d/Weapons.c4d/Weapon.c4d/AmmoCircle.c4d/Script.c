#strict 2
#appendto WP7A

func Initialize()
{
  var targetSize = 14;

  var id = GetID();
  var pictureWidth = GetDefCoreVal("Picture", 0, id, 2);
  var pictureHeight = GetDefCoreVal("Picture", 0, id, 3);

  SetGraphics(0, this, AC7A, GFX_Overlay, GFXOV_MODE_Picture);
  SetObjDrawTransform(1000 * targetSize / pictureWidth, 0, (pictureWidth - targetSize) * 500, 0, 1000 * targetSize / pictureHeight, (pictureHeight - targetSize) * 500, this, GFX_Overlay);

  return _inherited(...);
}

func UpdateAmmoBar()
{
  var ammo = this->GetAmmoPercent() / 5;
  if(ammo) ammo = Format("%d", ammo);
  SetGraphics(ammo, this, AC7A, GFX_Overlay, GFXOV_MODE_Picture);

  return _inherited(...);
}

func Activated()
{
  SetClrModulation(RGB(119,173,202), this, GFX_Overlay);

  return _inherited(...);
}

func Deactivated()
{
  SetClrModulation(RGB(255,255,255), this, GFX_Overlay);

  return _inherited(...);
}