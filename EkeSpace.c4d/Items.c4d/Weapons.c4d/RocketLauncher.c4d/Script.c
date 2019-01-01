/* Raketenwerfer */
#strict 2
#include WP7A

func ActionString() { return "RocketLauncher"; }

func NeedsActivation() { return true; }

func ShotDelay() { return [30]; }
func AmmoID() { return MS7A; }
func AmmoUsage() { return [1000]; }
func ShotSound() { return ["RL_Shoot"]; }
func ReloadSound() { return "RL_Reload"; }
func EmptySound() { return ["PT_Empty"]; }

func Fire(object clonk, int dir, int mode)
{
    dir = dir * 2 - 1;

    var missile = CreateContents(MS7A);

    var x = dir * 10;
    var y = 2;
    var r = dir * (90 + shootingAxis * 22);

    SetDir(dir, missile);
    Exit(missile, x, y, r);
    SetController(GetController(clonk), missile);
    missile->Launch(this);
}