/*-- Arrays --*/

#strict 2

// Löscht ein Item aus einem Array
global func DeleteArrayItem(int iNumber, & aArray) {
  var aTemp = [];
  for(var i; i<GetLength(aArray); i++) {
    if(i == iNumber) continue;
    var iDif = 0;
    if(i > iNumber) iDif = -1;
    aTemp[i+iDif] = aArray[i];
  } 
  aArray = aTemp;
  return aArray;
}

//Prüft, ob ein Eintrag im Array sitzt. (bool)
global func PartOf(value, array aArray)
{
  for(var i=0; i<GetLength(aArray); i++)
    if(aArray[i] == value)
      return true;
  return false;
}

//Sucht den Index eines Item in einem Array (int)
global func GetArrayItemPosition(MyValue, aArray) {
  var iNumber = -1;
  for(var i = 0; i < GetLength(aArray); i++) {
    if(aArray[i] == MyValue) {
      iNumber=i;
      break;
    }
    else 
      continue;
  }
  return iNumber;
}

global func ConcatArray(aArray, array aArrayToAdd) {
  var aArrayTemp = aArray;
  for(var i = 0; i < GetLength(aArrayToAdd); i++)
    aArrayTemp[GetLength(aArrayTemp)] = aArrayToAdd[i];
  return aArrayTemp;
}
