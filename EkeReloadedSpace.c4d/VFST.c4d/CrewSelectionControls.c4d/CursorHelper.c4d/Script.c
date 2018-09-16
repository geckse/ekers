#strict 2

func CrewSelection(bool deselect, bool cursorOnly)
{
	var clonk = FindObject2(Find_ID(VSFT), Find_Owner(GetOwner()), Find_OCF(OCF_CrewMember));
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

