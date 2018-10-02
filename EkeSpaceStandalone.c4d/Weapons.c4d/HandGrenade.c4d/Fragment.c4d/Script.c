/* Fragment */

#strict

func Initialize()
{
  SetAction("Fly");
  return(1);
}

func FlyingFX()
{
  // über den oberen Rand hinaus?
  if (GetY() < -10) return(RemoveObject());

  var size = 20 + ((50 - GetActTime()) * Random(5) + 1);
  var color = RGBa(255, 255, 255, 255 - size);

  CreateParticle("Fire2", 0, 0, 0, 0, size, color);
  return(1);
}

func Hit()
{
  SetAction("FadeOut");
  SetCategory(1);
  return(1);
}

func FadeOut()
{
  var alpha = GetActTime();
  if (alpha == 255)
  {
    RemoveObject();
    return(1);
  }
  SetClrModulation(RGBa(255, 255, 255, alpha));
  return(1);
}