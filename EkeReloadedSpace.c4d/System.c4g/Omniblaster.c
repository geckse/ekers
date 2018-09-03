#strict 2
#appendto OB5B

func BlowUp()
{
  CreateObject(PEXP,0,0,GetOwner())->init(); 
  RemoveObject();
  return(1);
}