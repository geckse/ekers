/*-- VSFT AppendTo --*/

#strict 2
#appendto VSFT

// don't collect rocks
public func RejectCollect(id idObject, object pObject) {
    if (idObject == ROCK) {
        return(1);
    }
    return _inherited(idObject, pObject);
}