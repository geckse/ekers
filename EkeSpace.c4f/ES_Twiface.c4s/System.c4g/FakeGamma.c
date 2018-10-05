/*-- Neues Script --*/

#strict
#appendto FGAM

public func Init(){
 iA = 190;
 wA = 190; // Erstmal nicht sichtbar
 wR = 54;
 wG = 22;
 wB = 64;
 iR = wR;
 iG = wG;
 iB = wB;
 SetObjDrawTransform (2000000, 0, 1000, 0, 2000000, 1000, this());
 }