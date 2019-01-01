#strict 2
#appendto CLNK

func Initialize()
{
	if(!FindObject(CS7I))
	{
		CreateObject(CS7I);
	}

	return _inherited(...);
}