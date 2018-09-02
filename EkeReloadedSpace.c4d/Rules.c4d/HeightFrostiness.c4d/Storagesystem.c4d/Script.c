/*-- Neues Objekt --*/

#strict

local aMetal;
local aOil;
local aCrys;
local aBio;

local aMaxStorage;

func Initialize() {
 aMetal = [];
 aOil = [];
 aCrys = [];
 aBio = [];
 aMaxStorage = [];
  return(1);
}
public func InitPlayer(int iPlr){
 aMetal[iPlr] = 0;
 aOil[iPlr] = 0;
 aCrys[iPlr] = 0;
 aBio[iPlr] = 0;
 aMaxStorage[iPlr] = 80;
 CreateObject(GH0D,0,0,iPlr)->Set(iPlr,"Wood",0);
 CreateObject(GH0D,0,0,iPlr)->Set(iPlr,"Rock",46);
 CreateObject(GH0D,0,0,iPlr)->Set(iPlr,"Gold",92);
 CreateObject(GH0D,0,0,iPlr)->Set(iPlr,"Coal",138);
 CreateObject(GH0D,0,0,iPlr)->Set(iPlr,"Ore",184);
 return(iPlr);
}
global func GetMat(int iPlr, string mat){
 var obj = FindObject(SSYS);
 if(!obj){
  Log("Storagesystem-Error: No Storagesystem created.");
  return(0);
 }
  return(obj->~SysGetMat(iPlr,mat));
}

public func SysGetMat(int iPlr, string mat){
  if(mat S= "Metal") return(aMetal[iPlr]);
  if(mat S= "Oil") return(aOil[iPlr]);
  if(mat S= "Crys") return(aCrys[iPlr]);
  if(mat S= "Bio") return(aBio[iPlr]);
  }

public func DoMaterial(int iPlr,string mat, int change){
 if(mat S= "Metal"){
   aMetal[iPlr] += change;
   if(aMetal[iPlr] < 0) aMetal[iPlr] = 0;
  }
 if(mat S= "Oil"){
   aOil[iPlr] += change;
   if(aOil[iPlr] < 0) aOil[iPlr] = 0;
  }
 if(mat S= "Crys"){
   aCrys[iPlr] += change;
   if(aCrys[iPlr] < 0) aCrys[iPlr] = 0;
  }
 if(mat S= "Bio"){
   aBio[iPlr] += change;
   if(aBio[iPlr] < 0) aBio[iPlr] = 0;
  }
  return(change);
 }