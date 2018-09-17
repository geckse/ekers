/*-- Stalaktit --*/

#strict 2

local iPhase;

func Initialize() 
{
  SetAction("Hanging");
  AddEffect("Search",this,100,3,this);
  iPhase = Random(4);
  SetPhase(iPhase);
  return true;
}

func FxGrowTimer(object pTarget, int iIndex, int iTime)
{
  if(iTime >= 500) 
  {
    RemoveEffect("Grow",pTarget);
    AddEffect("Search",pTarget,100,1,pTarget); 
    return true;
  }
  SetObjDrawTransform(1000,0,0,0,2*iTime,iTime*38-20000,pTarget);
  //SetObjDrawTransform(1000,0,0,0,10*iTime,iTime*190-20000,pTarget);
  return true;
}

func FxSearchTimer(object pTarget)
{
  if(GetAction(pTarget) == "Hanging")
  {
    if(GetEffect("Grow",pTarget)) return false;
    //Suchhöhe passend einschränken = Performance ++;
    var iHeight = GetGround(GetX(pTarget),GetY(pTarget)) - GetY(pTarget);
    for(var clonk in FindObjects(Find_OCF(OCF_CrewMember),Find_NoContainer(),Find_InRect(-25,0,50,iHeight)))
      if(PathFree(GetX(pTarget),GetY(pTarget),GetX(clonk),GetY(clonk)))
        if(GetAlive(clonk))
          if(!Random(2))
          {
            var pNew = CreateObject(GetID(pTarget),0,19,GetOwner(pTarget));
            SetObjDrawTransform(1000,0,0,0,0,0,pNew);
            AddEffect("Grow",pNew,100,1,pNew);
            Sound("Earthquake"); 
            SetAction("Falling");
            SetPhase(iPhase);
            RemoveVertex(0);
            RemoveVertex(0);
          }
    return true;
  }
  if(GetAction(pTarget) == "Falling")
  {
    for(var clonk in FindObjects(Find_OCF(OCF_Living),Find_NoContainer(),Find_InRect(-7,-19,14,50)))
      DoEnergy(-Random(2),clonk);
    return true;
  }
  return false;
}

func Hit() 
{
  Sound("RockBreak*");
  Sound("Blast2",0,0,50);
  Split(-4,-4,"Exist",iPhase*2);
  Split(3,-4,"Exist",iPhase*2+1);
  Split(0,12,"LameExist",iPhase);	
  RemoveObject(this);
}

func Split(int iX, int iY, string szAction, int iActPhase)
{
  var pSplinter = CreateObject(SP0D,iX,iY);
  ObjectSetAction(pSplinter,szAction);
  SetPhase(iActPhase);
  SetRDir(Random(20)-10,pSplinter);
  SetSpeed(Random(30)-15,-Random(35)+10,pSplinter);
  return pSplinter;
}

global func PlaceStalaktite(int iX, int iY, int iWidth, int iHeight, int iRetries)
{
  for(var i; i <= iRetries; i++)
  {
    var x = Random(iWidth)+iX;
    var y = Random(iHeight)+iY;
    var mat  = GetMaterial(x,y-10);
    if(!GBackSolid(AbsX(x),AbsY(y)))
      if(mat == Material("Rock") || mat == Material("Granite"))
        return CreateObject(SL0D,AbsX(x),AbsY(y)+30);
  }
  return true;
}

//Deckenhöhe finden finden
global func GetCeiling(x, y)
{
  if(!GBackSemiSolid(AbsX(x),AbsY(y)))
  {
    for(var i = y; --i; i > 0)
    {
      if(GBackSemiSolid(AbsX(x),AbsY(i))) return i;
    }
    return i;
  }
  else
  {
    for(var i = y; i < LandscapeHeight()-1; ++ i)
    {
      if(!GBackSemiSolid(x-GetX(),i-GetY())) return i-1;
    }
    return i;
  }
}

//Boden finden
global func GetGround(x, y)
{
  if(GBackSemiSolid(x-GetX(),y-GetY()))
  {
    for(var i = y; --i; i > 0)
    {
      if(!GBackSemiSolid(x-GetX(),i-GetY())) return i;
    }
    return i;
  }
  else
  {
    for(var i = y; i < LandscapeHeight()-1; ++ i)
    {
      if(GBackSemiSolid(x-GetX(),i-GetY())) return i-1;
    }
    return i;
  }
}
