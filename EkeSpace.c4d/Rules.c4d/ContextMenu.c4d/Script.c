/* Kontextmenü */

#strict

protected func Activate(player)
{
  var clonk = GetCursor(player);  

  if (Contained(clonk))
  {
    var b1 = Contained(clonk) -> GetCategory() & C4D_Structure;
    var b2 = Contained(clonk) -> GetCategory() & C4D_Vehicle;
    
    if (b1 || b2) return(OpenContextMenu(clonk, Contained(clonk)));
  }
  var b3 = GetAction(clonk) eq "Push";
  var b4 = Contents(0, clonk);
  
  if (b3) return(OpenContextMenu(clonk, GetActionTarget(0, clonk)));
  if (b4) return(OpenContextMenu(clonk, Contents(0, clonk)));

  OpenContextMenu(clonk, clonk);
}

private func OpenContextMenu(clonk, stuff)
{
  SetCommand(clonk, "Context", 0, 0, 0, stuff);
}