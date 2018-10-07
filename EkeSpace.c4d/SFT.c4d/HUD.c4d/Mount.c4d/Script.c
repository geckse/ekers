/*-- Energy Bar --*/

#strict 2

func Initialize()
{
	SetVisibility(VIS_None);
	return true;
}

func AttachTargetLost()
{
	RemoveObject();
}