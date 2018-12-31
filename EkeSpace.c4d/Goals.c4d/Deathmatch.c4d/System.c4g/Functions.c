#strict 2

/*------------------------------------*\
    Clonk Spawn/Respawn
\*------------------------------------*/
global func SpawnClonk(clonk)
{
    if(!deathmatchRule) return _inherited(clonk, ...);
    
    // move new clonk to random respawn point, avoid spawning by hostiles
    var wipf = PlaceAnimal(WIPF);
    var spawnX = GetX(wipf);
    var spawnY = GetY(wipf);
    RemoveObject(wipf);

    for(var i = 1; i <= 4; i++) {
        var a2 = Find_Hostile(GetController(clonk));
        var a3 = Find_OCF(OCF_Alive);
        var a4 = Find_NoContainer();
        var a5 = Find_Distance(150, spawnX, spawnY);
        var hostile = FindObject2(a2, a3, a4, a5);
        if(hostile) {
            wipf = PlaceAnimal(WIPF);
            spawnX = GetX(wipf);
            spawnY = GetY(wipf);
            RemoveObject(wipf);
        }
    }
    SetPosition(spawnX, spawnY, clonk);

    // equip clonk
    var assaultRifle = CreateContents(AR7A, clonk);
    assaultRifle->SetAmmoPercent(100);
    CreateContents(HG7A, clonk,1);
    return(1);
}