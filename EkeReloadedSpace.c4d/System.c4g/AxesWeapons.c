/*-- Bullet Axes --*/

#strict 2
#appendto AR5B
#appendto PT5B
#appendto SG5B
#appendto UZ5B

static iBulletAxis = 1;

// change shooting axis by pressing "dig"
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