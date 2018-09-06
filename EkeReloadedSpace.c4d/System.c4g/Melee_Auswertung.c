/*-- Neues Script --*/

#strict 2
#appendto MELE

public func IsFulfilled()
{
  var iFulFil = _inherited(...);
  if(iFulFil)
  {
              var allPlr;
              for(var i=0; i<GetPlayerCount(); i++)
               {
                var iPlr = GetPlayerByIndex(i);
                if(!aPlrEvaluated[iPlr]) AddEvaluationData(EvaDataPlr(iPlr),GetPlayerID(iPlr));
               }
  }
  return iFulFil;
}