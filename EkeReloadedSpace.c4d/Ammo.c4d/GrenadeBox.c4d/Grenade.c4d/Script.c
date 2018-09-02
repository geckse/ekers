/* Granate */

#strict

local xDir;
local yDir;
local lastX;
local lastY;
local stop;
local shooter;

func Launch(clonk)
{
  shooter = clonk;
  SetAction("Fly");
  return(1);
}
  
func Flying()
{
  if (EkeFindVictim(-5, -10, 10, 20, shooter)) return(BlowUp());
  if (stop > 5)                                return(BlowUp());

  if ((GetX() != lastX) || (GetY() != lastY)) stop = 0;

  lastX = GetX();
  lastY = GetY();
  
  stop++;
}

func ContactLeft()
{
  xDir = -2 * GetXDir() / 3;
  yDir = +2 * GetYDir() / 3;
  return(1);
}

func ContactRight()
{
  xDir = -2 * GetXDir() / 3;
  yDir = +2 * GetYDir() / 3;
  return(1);
}

func ContactTop()
{
  xDir = +2 * GetXDir() / 3;
  yDir = -2 * GetYDir() / 3;
  return(1);
}

func ContactBottom()
{
  xDir = +2 * GetXDir() / 3;
  yDir = -2 * GetYDir() / 3;
  return(1);
}

func BlowUp()
{
  Schedule("Explode(20)", 1);
  return(1);
}    

func Hit()
{
  shooter = 0;  

  SetXDir(xDir);
  SetYDir(yDir);

  Sound("GR_Hit*");
  return(1);  
}

func Damage()
{
  if (GetDamage() < 1) return(1);
  return(BlowUp());
}