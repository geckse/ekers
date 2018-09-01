/*-- Neues Script --*/

#strict
#appendto VSFT

private func CanGetOnAirbike()
{
  var airbike = FindObject2(Find_ID(AB7A),
                            Find_Distance(10),
                            Find_NoContainer());

  if (!airbike)                             return(0);
  if (GetAction() eq "Push")                return(0);
  if (!(airbike -> ControlRequest(this()))) return(0);

  return(1);
}

private func CheckArmed()
{
  if (GetAction() eq "AirbikeFly") return(0);

  ScrollHud(LocalN("mode", Contents()));
  SetAmmoBar(LocalN("ammo", Contents()));

  if (GetAction() eq "Walk") if (GetID(Contents()) == PT5B) return(SetActionSmooth("PistolWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == PT5B) return(SetActionSmooth("PistolJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == PT5B) return(SetActionSmooth("PistolJump"));
  if (GetAction() eq "Swim") if (GetID(Contents()) == PT5B) return(SetActionSmooth("PistolSwim"));
  if (GetAction() eq "PistolWalk") if (GetID(Contents()) != PT5B) return(SetActionSmooth("Walk"));
  if (GetAction() eq "PistolJump") if (GetID(Contents()) != PT5B) return(SetActionSmooth("Jump"));
  if (GetAction() eq "PistolSwim") if (GetID(Contents()) != PT5B) return(SetActionSmooth("Swim"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == UZ5B) return(SetActionSmooth("UziWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == UZ5B) return(SetActionSmooth("UziJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == UZ5B) return(SetActionSmooth("UziJump"));
  if (GetAction() eq "Swim") if (GetID(Contents()) == UZ5B) return(SetActionSmooth("UziSwim"));
  if (GetAction() eq "UziWalk") if (GetID(Contents()) != UZ5B) return(SetActionSmooth("Walk"));
  if (GetAction() eq "UziJump") if (GetID(Contents()) != UZ5B) return(SetActionSmooth("Jump"));
  if (GetAction() eq "UziSwim") if (GetID(Contents()) != UZ5B) return(SetActionSmooth("Swim"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == FT5B) return(SetActionSmooth("FlamethrowerWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == FT5B) return(SetActionSmooth("FlamethrowerJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == FT5B) return(SetActionSmooth("FlamethrowerJump"));
  if (GetAction() eq "Swim") if (GetID(Contents()) == FT5B) return(SetActionSmooth("FlamethrowerSwim"));
  if (GetAction() eq "FlamethrowerWalk") if (GetID(Contents()) != FT5B) return(SetActionSmooth("Walk"));
  if (GetAction() eq "FlamethrowerJump") if (GetID(Contents()) != FT5B) return(SetActionSmooth("Jump"));
  if (GetAction() eq "FlamethrowerSwim") if (GetID(Contents()) != FT5B) return(SetActionSmooth("Swim"));


  if (GetAction() eq "Walk") if (GetID(Contents()) == IT5B) return(SetActionSmooth("IcethrowerWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == IT5B) return(SetActionSmooth("IcethrowerJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == IT5B) return(SetActionSmooth("IcethrowerJump"));
  if (GetAction() eq "Swim") if (GetID(Contents()) == IT5B) return(SetActionSmooth("IcethrowerSwim"));
  if (GetAction() eq "IcethrowerWalk") if (GetID(Contents()) != IT5B) return(SetActionSmooth("Walk"));
  if (GetAction() eq "IcethrowerJump") if (GetID(Contents()) != IT5B) return(SetActionSmooth("Jump"));
  if (GetAction() eq "IcethrowerSwim") if (GetID(Contents()) != IT5B) return(SetActionSmooth("Swim"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == AR5B) return(SetActionSmooth("AssaultRifleWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == AR5B) return(SetActionSmooth("AssaultRifleJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == AR5B) return(SetActionSmooth("AssaultRifleJump"));
  if (GetAction() eq "Swim") if (GetID(Contents()) == AR5B) return(SetActionSmooth("AssaultRifleSwim"));
  if (GetAction() eq "AssaultRifleWalk") if (GetID(Contents()) != AR5B) return(SetActionSmooth("Walk"));
  if (GetAction() eq "AssaultRifleJump") if (GetID(Contents()) != AR5B) return(SetActionSmooth("Jump"));
  if (GetAction() eq "AssaultRifleSwim") if (GetID(Contents()) != AR5B) return(SetActionSmooth("Swim"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == RL5B) return(SetActionSmooth("RocketLauncherWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == RL5B) return(SetActionSmooth("RocketLauncherJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == RL5B) return(SetActionSmooth("RocketLauncherJump"));
  if (GetAction() eq "Swim") if (GetID(Contents()) == RL5B) return(SetActionSmooth("RocketLauncherSwim"));
  if (GetAction() eq "RocketLauncherWalk") if (GetID(Contents()) != RL5B) return(SetActionSmooth("Walk"));
  if (GetAction() eq "RocketLauncherJump") if (GetID(Contents()) != RL5B) return(SetActionSmooth("Jump"));
  if (GetAction() eq "RocketLauncherSwim") if (GetID(Contents()) != RL5B) return(SetActionSmooth("Swim"));

  if (GetAction() eq "Walk") if (GetID(Contents()) == SG5B) return(SetActionSmooth("ShotgunWalk"));
  if (GetAction() eq "Jump") if (GetID(Contents()) == SG5B) return(SetActionSmooth("ShotgunJump"));
  if (GetAction() eq "Dive") if (GetID(Contents()) == SG5B) return(SetActionSmooth("ShotgunJump"));
  if (GetAction() eq "Swim") if (GetID(Contents()) == SG5B) return(SetActionSmooth("ShotgunSwim"));
  if (GetAction() eq "ShotgunWalk") if (GetID(Contents()) != SG5B) return(SetActionSmooth("Walk"));
  if (GetAction() eq "ShotgunJump") if (GetID(Contents()) != SG5B) return(SetActionSmooth("Jump"));
  if (GetAction() eq "ShotgunSwim") if (GetID(Contents()) != SG5B) return(SetActionSmooth("Swim"));

}