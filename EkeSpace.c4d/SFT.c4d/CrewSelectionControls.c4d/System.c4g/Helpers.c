#strict 2

static DT_CursorChange_LastCursors;

global func GetCrew(int plr, int index, bool includeHelpers)
{
	if(includeHelpers)
	{
		return inherited(plr, index);
	}

	var foundIndex = -1;
	for(var i = 0; i < GetCrewCount(plr); ++i)
	{
		var crew = inherited(plr, index);
		if(!crew || !crew->~IsCursorHelper())
		{
			if(++foundIndex == index)
			{
				return crew;
			}
		}
	}
}

global func GetCrewIndex(object crew)
{
	var plr = GetOwner(crew);

	for(var i = 0; i < GetCrewCount(plr); ++i)
	{
		if(GetCrew(plr, i, true) == crew)
		{
			return i;
		}
	}

	return -1;
}

global func GetCursorCount(int player)
{
	for(var i = 0; GetCursor(player, i); ++i);

	return i;
}

global func GetCursors(int player)
{
	var ret = [];
	for(var i = 0, cursor; cursor = GetCursor(player, i); ++i)
	{
		ret[GetLength(ret)] = cursor;
	}

	return ret;
}

global func SetCursors(int player, array cursors)
{
	UnselectCrew(player);

	if(!cursors || GetLength(cursors) == 0)
	{
		return;
	}

	for(var i = 1; i < GetLength(cursors); ++i)
	{
		SelectCrew(player, cursors[i], true, true);
	}
	SetCursor(player, cursors[0], ...);
}

global func CycleCursor(int player, bool backwards, object currentCursor)
{
	if(!GetCrew(player))
	{
		return;
	}

	var currentIndex = GetCrewIndex(currentCursor || GetCursor(player));

	// in my understanding, the left cursor changing key is forward, but in the means of indices it is backward
	// so forward means decreasing index
	var step = -1;
	if(backwards)
	{
		step = 1;
	}

	for(var crewCount = GetCrewCount(player); ;)
	{
		currentIndex += step;
		if(currentIndex < 0)
		{
			currentIndex += crewCount;
		}
		else if(currentIndex >= crewCount)
		{
			currentIndex -= crewCount;
		}

		var crew = GetCrew(player, currentIndex, true);
		if(!crew)
		{
			// break for now to avoid a possible endless loop
			return;
		}

		if(!crew->~IsCursorHelper())
		{
			UnselectCrew(player);
			SetCursor(player, crew, ...);
			return crew;
		}
	}
}

global func SetCursor()
{
	var oldStatus = DT_CursorChange_IgnoreChanges;
	DT_CursorChange_IgnoreChanges = true;
	var ret = inherited(...);
	DT_CursorChange_IgnoreChanges = oldStatus;
	return ret;
}

global func UnselectCrew()
{
	var oldStatus = DT_CursorChange_IgnoreChanges;
	DT_CursorChange_IgnoreChanges = true;
	var ret = inherited(...);
	DT_CursorChange_IgnoreChanges = oldStatus;
	return ret;
}

global func SelectCrew()
{
	var oldStatus = DT_CursorChange_IgnoreChanges;
	DT_CursorChange_IgnoreChanges = true;
	var ret = inherited(...);
	DT_CursorChange_IgnoreChanges = oldStatus;
	return ret;
}