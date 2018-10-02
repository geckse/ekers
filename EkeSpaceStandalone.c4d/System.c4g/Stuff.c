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