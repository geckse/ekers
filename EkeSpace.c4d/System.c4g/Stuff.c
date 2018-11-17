/* Stuff */

#strict

static const ekeVersion = 17;

global func EkeFindVictim(x, y, w, h, exclude)
{
  for (var victim in FindObjects(Find_InRect(x, y, w, h),
                                 Find_NoContainer(),
                                 Find_Exclude(exclude)))
  {
    var b0 = !ObjectCount(NF7A);
    var b1 = Hostile(GetController(), GetController(victim), 1);
    var b2 = GetOCF(victim) & OCF_Alive();
    var b3 = GetOCF(victim) & OCF_Container();
    var b4 = GetOCF(victim) & OCF_Grab();
    var b5 = GetOCF(victim) & OCF_Inflammable();

    if ((b0 || b1) && (b2 || b3 || b4 || (b1 && b5))) return(true);
  }
  return(false);
}

global func Normalize(int iAngle, int iStart, int iPrecision) {
  if(!iPrecision) iPrecision = 1;
  var iEnd = iPrecision*360+iStart;

  while(iAngle<iStart) iAngle += iPrecision*360;
  while(iAngle>=iEnd) iAngle -= iPrecision*360;

  return iAngle;
}

// Ziele finden:
// pObj - Objekt dass sucht
// maxDist - maximale Distanz
// maxAngle - maximaler Winkel im Suchtrichter (opt)
// angle - Richtung des Suchtrichters (opt)
// disregardLineOfSight - ob das Objekt hinter einr Wand ist, ist egal (opt)
global func FindTargets(object pObj, int maxDist, int maxAngle, int angle, bool disregardLineOfSight) {

  if(!pObj)
    pObj = this;

  if(!maxAngle)
    maxAngle = 180;

  var pT;
  var targets = CreateArray();

  var x = GetX(pObj);
  var y = GetY(pObj);

  var preTargets = FindObjects(
    Find_Distance(maxDist, AbsX(x), AbsY(y)),
    Find_Exclude(pObj),
    Find_NoContainer(),
    Find_OCF(OCF_Alive),
    Find_Hostile(GetController()),  // schon in CheckEnemy drin
    Sort_Distance()
  );

  for(pT in preTargets) {
    var ox = GetX(pT);
    var oy = GetY(pT);

    // Pfad frei
    if(!disregardLineOfSight)
      if(!PathFree(x,y,ox,oy))
        continue;

    // Im Suchkegel
    var diffAngle = Abs(Normalize(Angle(x,y,ox,oy)-angle,-180));
    if(diffAngle > maxAngle)
        continue;

    // dann rein in Ergebnismenge...
    targets[GetLength(targets)] = pT;
  }

  return targets;
}