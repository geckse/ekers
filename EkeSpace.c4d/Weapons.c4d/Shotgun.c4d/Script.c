/* Schrotflinte */

#strict 2
#include WP7A

func ActionString() { return "Shotgun"; }

func Modes() { return [false]; }
func ShotDelay() { return [30]; }
func AmmoID() { return CA7A; }
func AmmoUsage() { return [150]; }
func ShotSound() { return [false]; }
func ReloadSound() { return "SG_Reload"; }
func EmptySound() { return ["PT_Empty"]; }

func MuzzlePos() { return [8, -3, 1]; }
func MuzzleFlashData() { return ["EkeMuzzleFlash3", 17, -2, 90, 100]; }

func Fire(object clonk, int dir, int mode)
{
  for (var i = 0; i < 5; i++)
  {
    var bullet = CreateBullet(dir, clonk);
    if (i == 0) Sound("SG_Shoot", 0, bullet);
  }

  ScheduleCall(this, "Reloading", 10);

  return true;
}

func Reloading()
{
  if(!ammo) return;

  var clonk = Contained();
  if(clonk)
  {
    ScheduleCall(0, "CreateShell", 5, 0, GetDir(clonk));
    Sound("SG_Reload", 0, 0, 75);
  }
}
