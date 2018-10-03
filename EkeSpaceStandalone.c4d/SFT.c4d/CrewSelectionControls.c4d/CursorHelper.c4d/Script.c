#strict 2

func Recruitment()
{
	SetPlrViewRange(0);
}

func CrewSelection(bool deselect, bool cursorOnly)
{
	var clonk = GetCrew(GetOwner());
	if(cursorOnly)
	{
		if(!deselect)
		{
			if(clonk)
			{
				clonk->CursorChangeCombo(this);
			}
		}
	}
	else if(!deselect && clonk)
	{
		var cursor = GetCursor(GetOwner());
		if(cursor && (cursor->~IsSpellGUI()))
		{
			cursor->~CursorToggled();
		}
		// deselect when selected through CursorToggle or SelectAll
		SelectCrew(GetOwner(), this, false);
		clonk->CursorChangeCombo(0);
	}
}

func FindOrDie()
{
	if(!GetCrew(GetOwner()))
	{
		RemoveObject(this);
	}
}