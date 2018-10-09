#strict 2

#appendto SF7A

static const DT_CursorChange_Left = 7;
static const DT_CursorChange_Middle = 8;
static const DT_CursorChange_Right = 9;

static const ShootingAxis_Straight = 0;
static const ShootingAxis_Downwards = 1;
static const ShootingAxis_Upwards = -1;

func Initialize()
{
	UpdateCursorHelpers();

	if(!DT_CursorChange_LastCursors)
	{
		DT_CursorChange_LastCursors = [];
	}

	return _inherited(...);
}

func UpdateCursorHelpers()
{
	var plr = GetOwner();
	var cursors = FindObjects(Find_ID(DT_CursorChange_CursorHelper), Find_Owner(plr));

	if(GetLength(cursors) < 2)
	{
		for(var i = GetLength(cursors); i < 2; ++i)
		{
			MakeCrewMember(CreateObject(DT_CursorChange_CursorHelper, 0, 0, plr), plr);
		}
	}
}

func FixCursor(bool delayed)
{
	if(delayed)
	{
		return Schedule("FixCursor()", 1);
	}

	if(!GetAlive(this))
	{
		return;
	}

	var target = this;
	var cursor = GetCursor(GetOwner());
	cursor->~FixupCursor(true);
	SetCursor(GetOwner(), target, true, true, false);
	if(cursor != target)
	{
		SetCursor(GetOwner(), cursor, true, true, false);
	}
	cursor->~FixupCursor(false);
}

func ControlCursorChange(int direction)
{
	if(direction == DT_CursorChange_Left)
	{
		return this->~ControlCursorLeft();
	}
	else if(direction == DT_CursorChange_Middle)
	{
		return (GetCursorCount(GetOwner()) == GetCrewCount(GetOwner()) - 2 && this->~ControlCursorMiddleDouble()) || this->~ControlCursorMiddle();
	}
	else if(direction == DT_CursorChange_Right)
	{
		return this->~ControlCursorRight();
	}
}

func CrewSelection(bool deselect, bool cursorOnly)
{
	if(DT_CursorChange_IgnoreChanges)
	{
		return _inherited(deselect, cursorOnly, ...);
	}

	var owner = GetOwner();

	if(deselect)
	{
		DT_CursorChange_LastCursors[owner] = this;
	}
	if(cursorOnly)
	{
		if(!deselect)
		{
			var last = DT_CursorChange_LastCursors[owner];
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
				var crewCount = GetCrewCount(owner);
				// wrap around?
				if(myIndex == 0)
				{
					myIndex = crewCount;
				}
				else if(myIndex == crewCount - 1)
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

			var prevent = false;
			if(diff == 1)
			{
				prevent = last->~ControlCursorChange(DT_CursorChange_Right);
			}
			else
			{
				prevent = last->~ControlCursorChange(DT_CursorChange_Left);
			}

			if(prevent)
			{
				UnselectCrew(owner);
				SetCursor(owner, last, true, true, false);
				last->~FixCursor(true);
				return;
			}
		}
	}
	return _inherited(deselect, cursorOnly, ...);
}

func Death()
{
	for(var helper in FindObjects(Find_ID(DT_CursorChange_CursorHelper), Find_Owner(GetOwner())))
	{
		helper->FindOrDie(this);
	}
	return _inherited(...);
}