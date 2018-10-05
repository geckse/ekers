#strict 2
#appendto SF7A

/*------------------------------------------*\
    Corpse Fade
\*------------------------------------------*/

func Initialize()
{
  AddEffect("SearchAndFade",this,100,80,this);
  return _inherited(...);
}

func FxSearchAndFadeTimer()
{
var pCorp = FindObject2(Find_Action ("Dead"),Find_Not(OCF_Alive));
  if(pCorp){
   if(!GetAlive(pCorp)){

     Schedule("FadeCorp(this())",RandomX(100,200),1,pCorp);
   }
  }      /*
var pCorpPart = FindObject2(Find_Func("CorpPart"));
  if(pCorpPart){
     Schedule("FadeCorp(this())",RandomX(100,200),1,pCorpPart);
  }        */
  return _inherited(...);
}
global func FadeCorp(object pCorp){
    if(pCorp->~CorpPart()){
      var width = 6;
      var height = 6;
            for(var x = -width/2; x < width/2; x++){
               var ix =  (GetDir()*2-1)*x;
               for(var y = -height/2; y < height/2; y++){
                 var eX = ix/4;
                 pCorp->~CreateParticle("CFSpark",ix,y,-eX,-RandomX(0,8),24,GetPlrColorDw(GetOwner(pCorp)) );
               }
              }
             RemoveObject(pCorp);
       return true;
    }
      var offx = pCorp->~GetActMapVal("Facet", GetAction(pCorp),0,0)+pCorp->~GetActMapVal("Facet", GetAction(pCorp),0,2)*(pCorp->~GetActMapVal("Length", GetAction(pCorp),0,0)-1);
      var offy = pCorp->~GetActMapVal("Facet", GetAction(pCorp),0,1);
      var width = pCorp->~GetActMapVal("Facet", GetAction(pCorp),0,2);
      var height = pCorp->~GetActMapVal("Facet", GetAction(pCorp),0,3);

      var dir = GetDir(pCorp);

        SetSolidMask(offx,offy,width,height,0,0,pCorp);

      for(var x = -width/2; x < width/2; x++){
       var ix =  (GetDir()*2-1)*x;
       for(var y = -height/2; y < height/2; y++){
        if(pCorp->~GBackSolid(ix,y)){
         var eX = ix/4;
         pCorp->~CreateParticle("CFSpark",ix,y,-eX,-RandomX(0,8),24,GetPlrColorDw(GetOwner(pCorp)) );
        }
       }
      }
      RemoveObject(pCorp);
 }