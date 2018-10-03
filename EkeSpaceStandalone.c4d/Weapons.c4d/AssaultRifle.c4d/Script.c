/* Sturmgewehr */

#strict 2
#include WP7A

func ActionString() { return "AssaultRifle"; }

func Modes() { return ["Cartridges", "Grenades"]; }
func Automatic() { return [true, false]; }
func ShotDelay() { return [4, 10]; }
func StopDelay() { return [10, 10]; }
func AmmoID() { return [CA7A, GB7A]; }
func AmmoUsage() { return [1, 10]; }
func ShotSound() { return ["AR_Shoot", "GR_Shoot"]; }
func ReloadSound() { return ["AR_Reload", "GR_Reload"]; }
func EmptySound() { return ["PT_Empty", "PT_Empty"]; }

func MuzzlePos() { return [4, 0]; }
func MuzzleFlashData() { return ["EkeMuzzleFlash2", 16, -1, 90, 85]; }

func Fire(object clonk, int dir, int mode)
{
	if(mode == 1)
	{
		CreateGrenade(GetDir(clonk), clonk);
		return true;
	}
	return _inherited(clonk, dir, mode, ...);
}

func CreateGrenade(dir, clonk)
{
	var x = 8 * dir - 4;
	var y = 1;

	var xDir = 20 * dir - 10;
	var yDir = -1 + shootingAxis * 4;

	var grenade = CreateContents(GR7A);
	Exit(grenade, x, y, 0, xDir, yDir);
	grenade -> Launch(clonk);
	SetController(GetController(clonk), grenade);
	return true;
}