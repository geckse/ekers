#strict 2

#appendto SF7A

static const DT_CursorChange_Next = 7;
static const DT_CursorChange_Toggle = 8;
static const DT_CursorChange_Prev = 9;

static const ShootingAxis_Straight = 0;
static const ShootingAxis_Downwards = 1;
static const ShootingAxis_Upwards = -1;

local cursorPrev, cursorNext, lastCursorToggleFrame;
local grabCursorChangesObject;

func Initialize()
{
	UpdateCursorHelpers();

	return _inherited(...);
}

func UpdateCursorHelpers()
{
	var plr = GetOwner();
	var cursors = FindObjects(Find_ID(_CCC), Find_Owner(plr));

	if(GetLength(cursors) == 0)
	{
		// order of next/prev is relevant
		MakeCrewMember(cursorNext = CreateObject(_CCC, 0, 0, plr), plr);
		MakeCrewMember(cursorPrev = CreateObject(_CCC, 0, 0, plr), plr);
	}
	else
	{
		cursorPrev = cursors[0];
		cursorNext = cursors[1];
	}
}

func FixCursor()
{
	if(!GetAlive(this))
	{
		return;
	}

	var target = grabCursorChangesObject || this;

	var cursor = GetCursor(GetOwner());
	cursor->~FixupCursor(true);
	SetCursor(GetOwner(), target, true, true, false);
	if(cursor != target)
	{
		SetCursor(GetOwner(), cursor, true, true, false);
	}
	cursor->~FixupCursor(false);
}

func CursorChangeCombo(object newCursor, bool fromComboMenu)
{
	SetCursor(GetOwner(), grabCursorChangesObject || this, true, true, false);
	Schedule("FixCursor()", 1); // otherwise the next key press will select the clonk even if the cursor changed already (e.g. to the aimer)

	var plr = GetOwner();
	var key;
	if(newCursor == cursorPrev || fromComboMenu)
	{
		key = DT_CursorChange_Prev;
	}
	else if(newCursor == cursorNext)
	{
		key = DT_CursorChange_Next;
	}
	else if(newCursor == 0 && lastCursorToggleFrame != FrameCounter())
	{
		lastCursorToggleFrame = FrameCounter();
		key = DT_CursorChange_Toggle;
	}

	if(key)
	{
		if(grabCursorChangesObject)
		{
			if(key == DT_CursorChange_Toggle)
			{
				SelectCrew(plr, this, false, true);
			}
			return grabCursorChangesObject->~CursorChanged(key, this);
		}

		if(key == DT_CursorChange_Prev)
		{
			ControlShoot(ShootingAxis_Downwards);
		}
		else if(key == DT_CursorChange_Next)
		{
			ControlShoot(ShootingAxis_Upwards);
		}
		else if(key == DT_CursorChange_Toggle)
		{
			ControlShoot(ShootingAxis_Straight);
		}
	}
}

func GrabCursorChanges(object obj)
{
	grabCursorChangesObject = obj;
}

func UngrabCursorChanges(object obj)
{
	if(grabCursorChangesObject == obj)
	{
		grabCursorChangesObject = 0;
	}
}

func Death()
{
	var ret = _inherited(...);

	if(cursorNext)
	{
		cursorNext->FindOrDie();
	}
	if(cursorPrev)
	{
		cursorPrev->FindOrDie();
	}

	return ret;
}

global func GetCrew(int plr, int index)
{
	for(;;++index)
	{
		var crew = _inherited(plr, index);
		if(!crew || GetID(crew) != _CCC)
		{
			return crew;
		}
	}
}