/* Pistole */

#strict 2
#include WP7A

func ActionString() { return "Pistol"; }

func NeedsActivation() { return true; }

func Modes() { return ["Pistol"]; }
func ShotDelay() { return [10]; }
func AmmoID() { return PM7A; }
func AmmoUsage() { return [150]; }
func ShotSound() { return [false]; }
func ReloadSound() { return "PT_Reload"; }
func EmptySound() { return ["PT_Empty"]; }

func MuzzlePos() { return [4, -1, 1]; }
func ShellPos() { return [5, -1, 1]; }
func MuzzleFlashData() { return ["EkeMuzzleFlash1", 14, -4, 90, 85]; }
