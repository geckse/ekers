// stippel player eliminates himself to trigger deathmatch goal

#strict 2
#appendto TE5B

func Initialize()
{
    AddEffect("Selfkill", this, 1, 100, this);
    return _inherited(...);
}
func FxSelfkillTimer()
{
    var owner = GetOwner();
    if(GetPlayerCount(C4PT_User) < 2) EliminatePlayer(owner, 1);
}