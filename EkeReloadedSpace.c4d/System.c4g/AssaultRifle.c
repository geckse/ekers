/*-- Assault Rifle Adds --*/

#strict 2
#appendto AR5B

static iBulletAxis;

func Initialize()
{
  mode = "Cartridges";
  iBulletAxis = 1;
  return(1);
}

// mit Graben Schussachse ändern
func ControlDigSingle()
{  
    return(1);
}
func ControlDig()
{
    iBulletAxis++;
    if (iBulletAxis > 3) {
        iBulletAxis = 1;
    }
    return(1);
}