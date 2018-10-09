#strict 2

static DT_CursorChange_IgnoreChanges;
static DT_CursorChange_LastToggleFrames;
static DT_CursorChange_LastDeselectCounts;

static const DT_CursorChange_NoTouch = 2;

static const DT_CursorChange_CursorHelper = CH7I;

func Recruitment()
{
	SetPlrViewRange(0);

	if(Contained())
	{
		Exit();
	}

	SetPosition(0, 0);
}

func CrewSelection(bool deselect, bool cursorOnly)
{
	if(DT_CursorChange_IgnoreChanges)
	{
		return;
	}

	var owner = GetOwner();
	var prevent = false;
	var last = DT_CursorChange_LastCursors[owner];
	if(!GetAlive(last))
	{
		last = 0;
	}

	if(cursorOnly)
	{
		if(!deselect)
		{
			if(!last)
			{
				return _inherited(deselect, cursorOnly, ...);
			}

			var lastIndex = GetCrewIndex(last);
			var myIndex = GetCrewIndex(this);
			if(myIndex == lastIndex || myIndex == -1 || lastIndex == -1)
			{
				return _inherited(deselect, cursorOnly, ...);
			}

			var diff = myIndex - lastIndex;
			if(Abs(diff) != 1)
			{
				// wrap around?
				if(myIndex == 0)
				{
					myIndex = GetCrewCount(owner);
				}
				else if(myIndex == GetCrewCount(owner) - 1)
				{
					myIndex = -1;
				}

				diff = myIndex - lastIndex;

				if(Abs(diff) != 1)
				{
					// not a difference of 1, maybe changed through mouse?
					return _inherited(deselect, cursorOnly, ...);
				}
			}

			if(diff == 1)
			{
				prevent = last->~ControlCursorChange(DT_CursorChange_Right);
			}
			else
			{
				prevent = last->~ControlCursorChange(DT_CursorChange_Left);
			}

			if(!prevent)
			{
				CycleCursor(owner, diff == 1, 0, true, false, true);
			}
		}
	}
	else if(!deselect)
	{
		if(last)
		{
			var cursor = GetCursor(owner);
			if(cursor && (cursor->~IsSpellGUI()))
			{
				cursor->~CursorToggled();
			}
			// deselect when selected through CursorToggle or SelectAll
			SelectCrew(owner, this, false);
			if(CheckLastToggleFrame(owner))
			{
				// changing crew through right-click deselects all of the crew first, thus DeselectCount is 2 in that case and it should be ignored
				if(DeselectCount(owner) != 2)
				{
					prevent = last->~ControlCursorChange(DT_CursorChange_Middle);
				}
			}
		}
	}
	else
	{
		CountDeselects(owner);
	}

	if(prevent && prevent != DT_CursorChange_NoTouch)
	{
		UnselectCrew(owner);
		SetCursor(owner, last, true, true, false);
		last->~FixCursor(true);
		return;
	}
	return _inherited(deselect, cursorOnly, ...);
}

func FindOrDie(object oldClonk)
{
	if(oldClonk)
	{
		// avoid jumping away of the view
		SetPosition(GetX(oldClonk), GetY(oldClonk));
		ScheduleCall(this, "FindOrDie", 2);
		return;
	}

	if(!GetCrew(GetOwner()))
	{
		RemoveObject(this);
	}
	else
	{
		SetPosition(0, 0);
	}
}

func IsCursorHelper()
{
	return true;
}

func CheckLastToggleFrame(int player)
{
	if(!DT_CursorChange_LastToggleFrames)
	{
		DT_CursorChange_LastToggleFrames = [];
	}

	if(DT_CursorChange_LastToggleFrames[player] == FrameCounter())
	{
		DT_CursorChange_LastToggleFrames[player] = -1;
		return true;
	}
	DT_CursorChange_LastToggleFrames[player] = FrameCounter();
	return false;
}

func CountDeselects(int player)
{
	if(!DT_CursorChange_LastDeselectCounts)
	{
		DT_CursorChange_LastDeselectCounts = [];
	}

	if(!DT_CursorChange_LastDeselectCounts[player])
	{
		DT_CursorChange_LastDeselectCounts[player] = [];
	}

	if(DT_CursorChange_LastDeselectCounts[player][0] != FrameCounter())
	{
		DT_CursorChange_LastDeselectCounts[player] = [FrameCounter(), 0];
	}

	++DT_CursorChange_LastDeselectCounts[player][1];
}

func DeselectCount(int player)
{
	if(!DT_CursorChange_LastDeselectCounts)
	{
		return 0;
	}

	var playerCount = DT_CursorChange_LastDeselectCounts[player];
	return playerCount && playerCount[0] == FrameCounter() && playerCount[1];
}