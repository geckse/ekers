/*-- Neues Objekt --*/

#strict

local iR,wR;
local iG,wG;
local iB,wB;
local iA,wA;

local pClonk;

func Initialize() {
 SetPosition(0,0);
  return(1);
}
public func Set(object clonk){
 Init();
 pClonk = clonk; return(this());
  }
public func Init(){
 iA = 255;
 wA = 255; // Erstmal nicht sichtbar
 wR = 255;
 wG = 0;
 wB = 0;
 SetObjDrawTransform (2000000, 0, 1000, 0, 2000000, 1000, this());
 }

public func MyClonkActive(){
if(GetCursor(GetOwner(pClonk)) == pClonk) return(1); // Clonk angewählt.
 }

public func Check(){
 if(!pClonk) RemoveObject(this());
 if(MyClonkActive()){ SetVisibility(VIS_Owner); } else { SetVisibility(VIS_None); } // nur sichtbar wenn angewählt

 //UpdateView();

 SetClrModulation(RGBa(iR,iG,iB,iA));

 if(iR < wR) iR++;
 if(iR > wR) iR--;
 if(iG < wG) iG++;
 if(iG > wG) iG--;
 if(iB < wB) iB++;
 if(iB > wB) iB--;
 if(iA < wA) iA++;
 if(iA > wA) iA--;

}

public func UpdateView(){
 wR = 0; wB = 0; wG = 0; wA = 255;
 var pAsteo = FindObject2(Find_Func("IsAsteorid"),Find_Distance(80,GetX(pClonk),GetY(pClonk)));
 var pNebel = FindObject2(Find_Func("IsSensInf"),Find_Distance(80,GetX(pClonk),GetY(pClonk)));
 if(pAsteo){
  if(GetID(pAsteo) == ROAS) wR = 80; wB = 50; wG =65; wA = 196;

  }
 if(pNebel){
  if(GetID(pNebel) == QSMO) wR = 60; wB = 30; wG =23; wA = 112;

  }
}