#strict 2

global func GetName(object target, id id)
{
  if(id)
  {
    return inherited(target, id, ...);
  }

  return LocalN("clonkName", target || this) || inherited(target, ...);
}
