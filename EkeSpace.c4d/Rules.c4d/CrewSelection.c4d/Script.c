#strict 2

func Activate(int player)
{
	var cursor = GetCursor(player);
	if(!cursor)
	{
		return;
	}

	var selectionMark = cursor->CreateSelectMark();
	var menu = CreateNewMenu
	([
		Menu_Caption(GetName(this)),
		Menu_Symbol(GetID()),
		Menu_Object(cursor),
		Menu_Style_Context(),

		Menu_Factory([ObjectCallback("CrewFactory", true)], [player, selectionMark]),
		Menu_Accept()
	]);

	var effect = AddEffect("CleanupSelectionMark", menu, 1, 0, this, 0);
	EffectVar(0, menu, effect) = selectionMark;
	EffectVar(1, menu, effect) = player;

	return menu;
}

func CrewFactory(array args, int entryNumber)
{
	var player = args[0];
	var selectionMark = args[1];

	var entries = [];

	for(var i = GetCrewCount(player) - 1; i >= 0 ; --i)
	{
		var crew = GetCrew(player, i);
		if(crew)
		{
			var caption = GetName(crew);
			if(!IsCrewSelected(player, crew))
			{
				caption = Format("<c 888888>%s</c>", caption);
			}

			ArrayAppend(entries, Menu_Entry
			([
				Menu_Entry_Caption(caption),
				Menu_Entry_Symbol(GetID(crew)),

				Menu_Entry_Callbacks
				([
					Menu_Callback(ObjectCallback("CrewSelection", true), Menu_CallbackType_Defaults, [Menu_CallbackArg_Args, Menu_CallbackArg_Action, Menu_CallbackArg_MenuObject]),
					Menu_Callback(ObjectCallback("HighlightCrew", true), Menu_CallbackType_Selection, [Menu_CallbackArg_Args]),
					Menu_Callback(ObjectCallback("UnhighlightCrew", true), Menu_CallbackType_Deselection, [Menu_CallbackArg_Args])
				]),
				Menu_Entry_Args([player, crew, entryNumber, selectionMark])
			]));
			++entryNumber;
		}
	}

	return entries;
}

func CrewSelection(array args, int action, object currentCursor)
{
	if(action == Menu_CallbackType_Special2)
	{
		SelectCrew(args[0], args[1], !IsCrewSelected(args[0], args[1]));

		if(GetCursor(args[0]) != currentCursor)
		{
			Activate(args[0])->SelectEntry(args[2]);
			return Menu_React_Close;
		}
		return Menu_React_Refresh;
	}
	else
	{
		UnselectCrew(args[0]);
		SetCursor(args[0], args[1]);
		return Menu_React_Close;
	}
}

func HighlightCrew(array args)
{
	SetPlrView(args[0], args[1]);
	if(args[3])
	{
		args[3]->MarkObject(args[1]);
	}
}

func UnhighlightCrew(array args)
{
	if(args[3])
	{
		args[3]->Hide();
		SetPlrView(args[0], GetCursor(args[0]));
	}
}

func FxCleanupSelectionMarkStop(object target, int effectNumber, int reason, bool temp)
{
	if(!temp)
	{
		var selectionMark = EffectVar(0, target, effectNumber);
		if(selectionMark)
		{
			RemoveObject(selectionMark);
		}

		var player = EffectVar(1, target, effectNumber);
		SetPlrView(player, GetCursor(player));
	}
}

func IsCrewSelected(int player, object crew)
{
	for(var i = 0; i < GetCursorCount(); ++i)
	{
		if(GetCursor(player, i) == crew)
		{
			return true;
		}
	}

	return false;
}

// this is needed because GetSelectCount seems to not update immediately -.-
func GetCursorCount(int player)
{
	for(var i = 0; GetCursor(player, i); ++i);
	return i;
}