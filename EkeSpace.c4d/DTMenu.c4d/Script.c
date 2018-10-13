#strict 2

static const DT_Menu = MN7I;
static const DT_Menu_Combined = -1;
static const DT_Menu_MenuVar = -1;

// Enums and bitfields

static const DT_Menu_Settings_Symbol = 0;
static const DT_Menu_Settings_Object = 1;
static const DT_Menu_Settings_Extra = 2;
static const DT_Menu_Settings_Caption = 3;
static const DT_Menu_Settings_ExtraData = 4;
static const DT_Menu_Settings_Style = 5;
static const DT_Menu_Settings_KeepOpen = 6;
static const DT_Menu_Settings_Parent = 7;
static const DT_Menu_Settings_Size = 8;
static const DT_Menu_Settings_RefreshInterval = 9;
static const DT_Menu_Settings_Selection = 10;
static const DT_Menu_Settings_ConditionDisableMode = 11;
static const DT_Menu_Settings_ConditionAllowSelection = 12;
static const DT_Menu_Settings_Callbacks = 13;
static const DT_Menu_Settings_Decoration = 14;
static const DT_Menu_Settings_RequireAction = 15;
static const DT_Menu_Settings_KeepParentOnClose = 16;
static const DT_Menu_Settings_Vars = 17;

static const DT_Menu_KeepOpen_Not = 0x0;
static const DT_Menu_KeepOpen_Keep = 0x1;
static const DT_Menu_KeepOpen_Force = 0x2;
static const DT_Menu_KeepOpen_Permanent = 0x4;
static const DT_Menu_KeepOpen_Refresh = 0x8;
static const DT_Menu_KeepOpen_RefreshContinuously = 0x10;
static const DT_Menu_KeepOpen_Refresh_Mask = 0x18; // DT_Menu_KeepOpen_Refresh | DT_Menu_KeepOpen_RefreshContinuously

static const DT_Menu_Type_Setting = 0;
static const DT_Menu_Type_Entry = 1;
static const DT_Menu_Type_Factory = 2;

static const DT_Menu_Action_Normal = 0;
static const DT_Menu_Action_Special2 = 1;
static const DT_Menu_Action_Close = 2;

static const Menu_React_OverrideReaction = -1;
static const Menu_React_None = 0;
static const Menu_React_Close = 1;
static const Menu_React_Refresh = 2;
static const Menu_React_KeepOpen = 3;
static const Menu_React_Back = 4;
static const Menu_React_SelectionOffset = 5;
static const Menu_React_SelectionChange = 6;
static const Menu_React_ShowSubmenu = 7;

global func Menu_React_OffsetSelection(int offset) { return [Menu_React_SelectionOffset, offset]; }
global func Menu_React_OverrideSelection(int override) { return [Menu_React_SelectionChange, override]; }
global func Menu_React_Override(override) { return [Menu_React_OverrideReaction, override]; }

static const Menu_ConditionReact_Default = 0;
static const Menu_ConditionReact_Show = 1;
static const Menu_ConditionReact_Hide = 2;
static const Menu_ConditionReact_GrayOut = 3;
static const Menu_ConditionReact_CustomFormat = 4;

global func Menu_ConditionReact_CustomColor(int color) { return [Menu_ConditionReact_CustomFormat, Format("<c %x>%%s</c>", color)]; }
global func Menu_ConditionReact_Format(string format) { return [Menu_ConditionReact_CustomFormat, format]; }

static const Menu_Condition_Default = 0;
static const Menu_Condition_AllowSelection = 1;
static const Menu_Condition_DenySelection = 2;

static const DT_Menu_Entry_Caption = 0;
static const DT_Menu_Entry_Callbacks = 1;
static const DT_Menu_Entry_Symbol = 2;
static const DT_Menu_Entry_Count = 3;
static const DT_Menu_Entry_InfoCaption = 4;
static const DT_Menu_Entry_Extra = 5;
static const DT_Menu_Entry_XPar1 = 6;
static const DT_Menu_Entry_XPar2 = 7;
static const DT_Menu_Entry_Args = 8;
static const DT_Menu_Entry_Condition = 9;
static const DT_Menu_Entry_Placeholder = 10;

static const Menu_CallbackType_None = 0x0;
static const Menu_CallbackType_Special2 = 0x1;
static const Menu_CallbackType_Normal = 0x2;
static const Menu_CallbackType_Close = 0x4;
static const Menu_CallbackType_Selection = 0x8;
static const Menu_CallbackType_Deselection = 0x10;
static const Menu_CallbackType_ValueChanged = 0x20;
static const Menu_CallbackType_InputAborted = 0x40;
static const Menu_CallbackType_Defaults = 0x3; // Menu_CallbackType_Normal | Menu_CallbackType_Special2
static const Menu_CallbackType_All = 0x7f; // Menu_CallbackType_Normal | Menu_CallbackType_Special2 | Menu_CallbackType_Close | Menu_CallbackType_Selection | Menu_CallbackType_Deselection | Menu_CallbackType_ValueChanged | Menu_CallbackType_InputAborted

static const Menu_AdaptorType_Boolean = 0;
static const Menu_AdaptorType_Integer = 1;
static const Menu_AdaptorType_String = 2;
static const Menu_AdaptorType_ID = 3;
static const Menu_AdaptorType_Enum = 4;
static const Menu_AdaptorType_BitField = 5;

static const Menu_Adaptor_Limits_Max = 0x7fffffff;
static const Menu_Adaptor_Limits_Min = 0x80000000;

static const Menu_CallbackArg_All = -1;
static const Menu_CallbackArg_Action = 0;
static const Menu_CallbackArg_Symbol = 1;
static const Menu_CallbackArg_MenuObject = 2;
static const Menu_CallbackArg_Args = 3;
static const Menu_CallbackArg_NewSelection = 4;
static const Menu_CallbackArg_OldSelection = 5;
static const Menu_CallbackArg_NewValue = 6;
static const Menu_CallbackArg_OldValue = 7;
static const Menu_CallbackArg_FromSubmenu = 8;
static const Menu_CallbackArg_Menu = 9;
static const Menu_CallbackArg_Returned = 10;
static const Menu_CallbackArg_Menu = 11;
static const Menu_CallbackArg_EntryNumber = 12;

static const DT_Menu_Adaptor_Type = 0;
static const DT_Menu_Adaptor_Variable = 1;
static const DT_Menu_Adaptor_Callbacks = 2;
static const DT_Menu_Adaptor_MessageBoardText = 3;
static const DT_Menu_Adaptor_Limits = 4;
static const DT_Menu_Adaptor_StepSize = 5;
static const DT_Menu_Adaptor_LayoutVals = 6;
static const DT_Menu_Adaptor_NoEmptyString = 7;
static const DT_Menu_Adaptor_EntryIndex = 8;
static const DT_Menu_Adaptor_Mask = 9;
static const DT_Menu_Adaptor_WrapAround = 10;
static const DT_Menu_Adaptor_Args = 11;
static const DT_Menu_Adaptor_EnumSubmenu = 12;
static const DT_Menu_Adaptor_EnumSubmenuCaption = 13;
static const DT_Menu_Adaptor_EnumSubmenuSymbol = 14;
static const DT_Menu_Adaptor_EnumAllowUnknown = 15;
static const DT_Menu_Adaptor_EnumInline = 16;

static const Menu_Layout_Symbol = 1;
static const Menu_Layout_InfoCaption = 2;

static const Menu_Layout__CaptionPos = 3;
static const Menu_Layout__ValuePos = 4;
// static const Menu_Layout__InputValuePos = 5; TODO

static const Menu_Layout_Caption = 4;
static const Menu_Layout_Value = 8;
// static const Menu_Layout_InputValue = 16; TODO
static const Menu_Layout__NoFlagMask = 3;

// ----------------------------------------------------------------------------

local settings;
local entries;
local createEntries;
local entryCount;
local currentSelection;
local suspended;
local closing;
local msgBoardMode;
local msgBoardEntry;
local noSelectionCallbacks;
local subMenu;
local vars;

func Initialize()
{
	vars = [];
}

func Destruction()
{
	Close();
}

func Create(array cSettings, array cEntries)
{
	settings = cSettings;
	entries = [];
	createEntries = cEntries;
	currentSelection = -1;
	settings[DT_Menu_Settings_ConditionDisableMode] = settings[DT_Menu_Settings_ConditionDisableMode] || Menu_ConditionReact_Hide;
	entryCount = 0;

	if(settings[DT_Menu_Settings_Vars])
	{
		var settingVars = settings[DT_Menu_Settings_Vars];

		for(var i = 0; i < GetLength(settingVars); ++i)
		{
			if(settingVars[i])
			{
				vars[i] = settingVars[i];
			}
		}
		settings[DT_Menu_Settings_Vars] = 0;
	}

	var factoryArgs = [];
	factoryArgs[Menu_CallbackArg_Menu] = this;
	factoryArgs[Menu_CallbackArg_MenuObject] = settings[DT_Menu_Settings_Object];

	HandleEntries(createEntries, entryCount, entries, factoryArgs);

	if(settings[DT_Menu_Settings_Parent]) settings[DT_Menu_Settings_Parent]->Suspend();

	CreateMenu(settings[DT_Menu_Settings_Symbol], settings[DT_Menu_Settings_Object], this, settings[DT_Menu_Settings_Extra], settings[DT_Menu_Settings_Caption], settings[DT_Menu_Settings_ExtraData], settings[DT_Menu_Settings_Style], true, MN7I);

	if(GetType(settings[DT_Menu_Settings_Size]) == C4V_Array) SetMenuSize(settings[DT_Menu_Settings_Size][0], settings[DT_Menu_Settings_Size][1], settings[DT_Menu_Settings_Object]);

	AddEntries(entries);

	if(entryCount > 0)
	{
		SelectEntry(settings[DT_Menu_Settings_Selection]);
	}

	if(settings[DT_Menu_Settings_Decoration])
	{
		SetMenuDecoration(settings[DT_Menu_Settings_Decoration], settings[DT_Menu_Settings_Object]);
	}

	if(!GetEffect("Menu", this)) AddEffect("Menu", this, 1, 1, this, 0);
}

func SelectEntry(int selection)
{
	if(selection < 0) selection = entryCount + selection;
	SelectMenuItem(selection, settings[DT_Menu_Settings_Object]);
}

func ActivateEntry(int index, int action)
{
	if(index < 0) index = entryCount + index;
	if(index >= entryCount || index < 0)
	{
		return;
	}

	SelectEntry(index);

	var entry = entries[index];
	MenuItemCommand(entry[DT_Menu_Entry_Symbol], index, action);
}

func SubMenu()
{
	return subMenu;
}

func &Var(int index)
{
	return vars[index];
}

global func MenuVar(int index)
{
	return [DT_Menu_MenuVar, index];
}

/*func FxMenuStart(object target, int effectNumber, int temp)
{

}*/

func FxMenuTimer(object target, int effectNumber, int effectTime)
{
	if(!settings[DT_Menu_Settings_Object])
	{
		return Close();
	}
	else if(settings[DT_Menu_Settings_RequireAction])
	{
		var obj = settings[DT_Menu_Settings_Object];
		var requirement = settings[DT_Menu_Settings_RequireAction];
		if(GetAction(obj) != requirement[0] || (requirement[1] && GetActionTarget(0, obj) != requirement[1]))
		{
			return Close();
		}
	}

	if(suspended) return;

	if(msgBoardMode != 0 && !TestMessageBoard(GetOwner(settings[DT_Menu_Settings_Object]), true))
	{
		var entry = entries[msgBoardEntry];
		var args = entry[DT_Menu_Entry_Args];
		var reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_InputAborted, [Menu_CallbackType_InputAborted, entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args]]);
		if(reaction != Menu_React_None)
		{
			React(reaction, msgBoardEntry);
		}
		msgBoardMode = 0;
	}

	if(!GetMenu(settings[DT_Menu_Settings_Object]))
	{
		if(settings[DT_Menu_Settings_KeepOpen] & (DT_Menu_KeepOpen_Refresh_Mask | DT_Menu_KeepOpen_Force))
		{
			Refresh(currentSelection);
		}
		else
		{
			return FX_Execute_Kill;
		}
	}

	if(settings[DT_Menu_Settings_KeepOpen] & DT_Menu_KeepOpen_RefreshContinuously && !(effectTime % settings[DT_Menu_Settings_RefreshInterval]))
	{
		Refresh(currentSelection);
	}
}

func FxMenuStop(object target, int effectNumber, int reason, bool temp)
{
	if(temp)
	{
		return;
	}
	CloseMenu(settings[DT_Menu_Settings_Object]);
	if(settings[DT_Menu_Settings_Parent]) settings[DT_Menu_Settings_Parent]->Suspend(true);
	RemoveObject(this);
}

func BindCallbackArgs(array args, array binding)
{
	var ret = CreateArray(GetLength(binding));
	var i = 0;
	for(var arg in binding)
	{
		if(arg == Menu_CallbackArg_All)
		{
			ret[i] = args;
		}
		else
		{
			ret[i] = args[arg];
		}
		++i;
	}

	return ret;
}

func CallCallbacks(array callbacks, int type, array args, defaultRet, bool noGlobalCallbacks)
{
	var ret = defaultRet;

	args[Menu_CallbackArg_Menu] = this;

	if(callbacks)
	{
		for(var callback in callbacks)
		{
			if(callback[1] & type)
			{
				ret = CallA(callback[0], BindCallbackArgs(args, callback[2]));
				break;
			}
		}
	}


	if(!noGlobalCallbacks)
	{
		args[Menu_CallbackArg_Returned] = ret;
		var globalRet = CallCallbacks(settings[DT_Menu_Settings_Callbacks], type, args, defaultRet, true);
		if(GetType(globalRet) == C4V_Array && globalRet[0] == Menu_React_OverrideReaction)
		{
			ret = globalRet[1];
		}
	}

	return ret;
}

func Close(bool closeParents)
{
	closing = true;
	if(subMenu)
	{
		subMenu->Close();
	}
	if(closeParents && settings[DT_Menu_Settings_Parent]) settings[DT_Menu_Settings_Parent]->Close(true);
	RemoveEffect("Menu", this);
}

func Suspend(bool cont)
{
	if(suspended == !cont) return;
	if(suspended = !cont)
	{
		CloseMenu(settings[DT_Menu_Settings_Object]);
	}
	else if(!closing)
	{
		Refresh(currentSelection);
	}
}

func HandleEntries(array factoryEntries, int& i, array& ret, array& factoryArgs)
{
	for(var entry in factoryEntries)
	{
		if(entry[0] == DT_Menu_Type_Entry)
		{
			ret[i++] = entry[1];
		}
		else if(entry[0] == DT_Menu_Type_Factory)
		{
			factoryArgs[Menu_CallbackArg_Args] = entry[1][1];

			for(var callback in entry[1][0])
			{
				factoryArgs[Menu_CallbackArg_EntryNumber] = i;
				var factoryResult = CallA(callback, BindCallbackArgs(factoryArgs, entry[1][2]));
				if(GetType(factoryResult) == C4V_Array)
				{
					var newEntries = [];
					UncombineAndDistinguish(factoryResult, settings, newEntries);
					HandleEntries(newEntries, i, ret, factoryArgs);
				}
				else if(factoryResult == Menu_React_Close)
				{
					return Close();
				}
							}
		}
	}
}

func AddEntries(array& entries)
{
	for(var i = 0; i < GetLength(entries); ++i)
	{
		var entry = entries[i];
		var condition = entry[DT_Menu_Entry_Condition], conditionRet;
		var caption = entry[DT_Menu_Entry_Caption], noCommand = !entry[DT_Menu_Entry_Placeholder] || (entry[DT_Menu_Entry_Placeholder] != true && !entry[DT_Menu_Entry_Callbacks]);
		if(condition)
		{
			if(noCommand || condition[1] == Menu_Condition_DenySelection || (condition[1] == Menu_Condition_Default && !settings[DT_Menu_Settings_ConditionAllowSelection]))
			{
				noCommand = true;
			}

			conditionRet = CallA(condition[0], [entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args]]) || settings[DT_Menu_Settings_ConditionDisableMode];
			if(conditionRet == Menu_ConditionReact_Hide)
			{
				continue;
			}
			else if(conditionRet == Menu_ConditionReact_GrayOut)
			{
				caption = Format("<c 808080>%s</c>", caption);
			}
			else if(GetType(conditionRet) == C4V_Array && conditionRet[0] == Menu_ConditionReact_CustomFormat)
			{
				caption = Format(conditionRet[1], caption);
			}
			else
			{
				noCommand = false;
			}
		}

		var symbol = entry[DT_Menu_Entry_Symbol], symbolID = 0, deleteSymbol = 0;
		if(GetType(symbol) == C4V_Array)
		{
			if(GetType(symbol[0]) == C4V_C4ID)
			{
				symbolID = symbol[0];
				if(symbol[2])
				{
					symbol = [CreateSymbolDummy()->SetSymbol(symbolID, symbol[1])->SetColor(symbol[2]), true];
				}
				else if(symbol[1])
				{
					entry[DT_Menu_Entry_Extra] |= C4MN_Add_ImgIndexed;
					entry[DT_Menu_Entry_XPar1] = symbol[1];
				}
			}

			if(GetType(symbol[0]) == C4V_C4Object)
			{
				entry[DT_Menu_Entry_Extra] |= C4MN_Add_ImgObject;
				entry[DT_Menu_Entry_XPar1] = symbol[0];
				deleteSymbol = symbol[1];
				symbolID = GetID(symbol[0]);
			}
		}
		else
		{
			symbolID = symbol;
		}
		entry[DT_Menu_Entry_Symbol] = symbolID;

		entries[i] = entry;

		AddMenuItem(caption, !noCommand && "MenuItemCommand", symbolID, settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Count], i, entry[DT_Menu_Entry_InfoCaption], entry[DT_Menu_Entry_Extra], entry[DT_Menu_Entry_XPar1], entry[DT_Menu_Entry_XPar2]);

		if(deleteSymbol)
		{
			RemoveObject(deleteSymbol);
		}
	}
}

func React(reaction, int itemNumber, int refreshDelayed)
{
	if(reaction == Menu_React_Close)
	{
		Close(!settings[DT_Menu_Settings_KeepParentOnClose]);
	}
	else if(reaction == Menu_React_Back)
	{
		Close();
	}
	else if(reaction == Menu_React_Refresh || (settings[DT_Menu_Settings_KeepOpen] & DT_Menu_KeepOpen_Refresh))
	{
		Refresh(itemNumber, refreshDelayed);
	}
	else if(GetType(reaction) == C4V_Array)
	{
		var selection = currentSelection;
		if(reaction[0] == Menu_React_SelectionOffset)
		{
			selection += reaction[1];
			selection %= entryCount;
		}
		else if(reaction[0] == Menu_React_SelectionChange)
		{
			selection = BoundBy(reaction[1], 0, entryCount - 1);
		}

		if(selection != currentSelection)
		{
			SelectEntry(selection);
		}
	}
}

func CheckCondition(array entry)
{
	var condition = entry[DT_Menu_Entry_Condition];
	return !condition || (CallA(condition[0], [entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args]]) || settings[DT_Menu_Settings_ConditionDisableMode]) == Menu_ConditionReact_Show;
}

func MenuItemCommand(id ID, int itemNumber, int action)
{
	var entry = entries[itemNumber];
	var condition = entry[DT_Menu_Entry_Condition];
	action = action || Menu_CallbackType_Normal;
	var reaction;
	if(CheckCondition(entry))
	{
		reaction = CallCallbacks(entry[DT_Menu_Entry_Callbacks], action, [action, ID, settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args]]);
	}
	else
	{
		if(condition[1] == Menu_Condition_AllowSelection)
		{
			reaction = Menu_React_KeepOpen;
		}
		else
		{
			reaction = Menu_React_Refresh;
		}
	}
	React(reaction, itemNumber);
}

func SubmenuItemCallback(int action, object menuObject, args, array allArgs)
{
	allArgs[Menu_CallbackArg_Args] = args[1];
	var reaction = CallCallbacks(args[0], action, allArgs, Menu_React_None);

	if(((action & Menu_CallbackType_Defaults) && reaction == Menu_React_None) || reaction == Menu_React_ShowSubmenu)
	{
		subMenu = CreateNewMenu(args[2], settings, this);
		return Menu_React_None;
	}
	else
	{
		return reaction;
	}
}

func MenuQueryCancel(int selection, object menuObject)
{
	var reaction;
	if(selection != -1)
	{
		var entry = entries[selection];
		if(CheckCondition(entry))
		{
			reaction = CallCallbacks(entry[DT_Menu_Entry_Callbacks], Menu_CallbackType_Close, [Menu_CallbackType_Close, entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args]]);
		}

		React(reaction, selection, true);
	}

	if((settings[DT_Menu_Settings_KeepOpen] != DT_Menu_KeepOpen_Not && settings[DT_Menu_Settings_KeepOpen] != DT_Menu_KeepOpen_Permanent) || (reaction == Menu_React_KeepOpen))
	{
		return true;
	}
}

func OnMenuSelection(int selection, object menuObject)
{
	if(selection != currentSelection)
	{
		var oldSelection = currentSelection;
		var entry = entries[currentSelection];
		var deselectReaction = Menu_React_None;
		var selectReaction = Menu_React_None;
		if(!noSelectionCallbacks && CheckCondition(entry) && currentSelection != -1)
		{
			deselectReaction = CallCallbacks(entry[DT_Menu_Entry_Callbacks], Menu_CallbackType_Deselection, [Menu_CallbackType_Deselection, entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args], selection, oldSelection]);
		}

		entry = entries[currentSelection = selection];

		if(!noSelectionCallbacks && CheckCondition(entry))
		{
			selectReaction = CallCallbacks(entry[DT_Menu_Entry_Callbacks], Menu_CallbackType_Selection, [Menu_CallbackType_Selection, entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], entry[DT_Menu_Entry_Args], selection, oldSelection]);
		}

		if(deselectReaction != Menu_React_None)
		{
			React(deselectReaction, currentSelection);
		}

		if(selectReaction != Menu_React_None)
		{
			React(selectReaction, currentSelection);
		}
	}
}

func Refresh(int selection, bool delayed)
{
	if(suspended)
	{
		return;
	}

	if(delayed)
	{
		ScheduleCall(this, "Refresh", 1, 0, selection);
	}
	else
	{
		var disabledCallbacks;
		if(!noSelectionCallbacks)
		{
			disabledCallbacks = noSelectionCallbacks = true;
		}

		CloseMenu(settings[DT_Menu_Settings_Object]);
		Create(settings, createEntries);
		SelectEntry(BoundBy(selection, 0, entryCount - 1));

		if(disabledCallbacks)
		{
			noSelectionCallbacks = false;
		}
	}
}

// ----------------------------------------------------------------------------

global func Menu__Setting(array setting) { return [DT_Menu_Type_Setting, setting]; }

global func Menu_Symbol(id symbol) { return Menu__Setting([DT_Menu_Settings_Symbol, symbol]); }
global func Menu_Object(object obj) { return Menu__Setting([DT_Menu_Settings_Object, obj]); }
global func Menu__Extra(int extra, int data) { return Menu_Combined([Menu__Setting([DT_Menu_Settings_Extra, extra]), Menu_ExtraData(data)]); }
global func Menu_Size(int width, int height) { return Menu__Setting([DT_Menu_Settings_Size, [width, height]]); }
global func Menu_ExtraData(int data) { return Menu__Setting([DT_Menu_Settings_ExtraData, data]); }
global func Menu_Caption(string caption) { return Menu__Setting([DT_Menu_Settings_Caption, caption]); }
global func Menu_RefreshInterval(int interval) { return Menu__Setting([DT_Menu_Settings_RefreshInterval, interval + !interval]); }
global func Menu_Selection(int selection) { return Menu__Setting([DT_Menu_Settings_Selection, selection]); }
global func Menu__Style(int style) { return Menu__Setting([DT_Menu_Settings_Style, style]); }
global func Menu__KeepOpen(int mode) { return Menu__Setting([DT_Menu_Settings_KeepOpen, mode]); }

global func Menu_Extra_None() { return Menu__Extra(C4MN_Extra_None); }
global func Menu_Extra_Components() { return Menu__Extra(C4MN_Extra_Components); }
global func Menu_Extra_Value() { return Menu__Extra(C4MN_Extra_Value); }
global func Menu_Extra_MagicValue(int compare) { return Menu__Extra(C4MN_Extra_MagicValue, compare); }
global func Menu_Extra_Info() { return Menu__Extra(C4MN_Extra_Info); }
global func Menu_Extra_ComponentsMagic() { return Menu__Extra(C4MN_Extra_ComponentsMagic); }

global func Menu_Style_Normal() { return Menu__Style(C4MN_Style_Normal); }
global func Menu_Style_Context() { return Menu__Style(C4MN_Style_Context); }
global func Menu_Style_Info() { return Menu__Style(C4MN_Style_Info); }
global func Menu_Style_Dialog() { return Menu__Style(C4MN_Style_Dialog); }
global func Menu_Style_EqualItemHeight() { return Menu__Style(C4MN_Style_EqualItemHeight); }

global func Menu_DontKeepOpen() { return Menu__KeepOpen(DT_Menu_KeepOpen_Not); }
global func Menu_KeepOpen() { return Menu__KeepOpen(DT_Menu_KeepOpen_Keep); }
global func Menu_ForceKeepOpen() { return Menu__KeepOpen(DT_Menu_KeepOpen_Force); }
global func Menu_Refresh() { return Menu__KeepOpen(DT_Menu_KeepOpen_Refresh); }
global func Menu_RefreshContinuously(int interval) { return Menu_Combined([Menu__KeepOpen(DT_Menu_KeepOpen_RefreshContinuously), Menu_RefreshInterval(interval)]); }
global func Menu_Permanent() { return Menu__KeepOpen(DT_Menu_KeepOpen_Permanent); }

global func Menu_ConditionAllowSelection() { return Menu__Setting([DT_Menu_Settings_ConditionAllowSelection, true]);}
global func Menu_ConditionDenySelection() { return Menu__Setting([DT_Menu_Settings_ConditionAllowSelection, false]);}

global func Menu_Callbacks(array callbacks) { return Menu__Setting([DT_Menu_Settings_Callbacks, callbacks]); }
global func Menu_Decoration(id decoration) { return Menu__Setting([DT_Menu_Settings_Decoration, decoration]); }
global func Menu_RequireAction(string action, object target) { return Menu__Setting([DT_Menu_Settings_RequireAction, [action, target]]); }
global func Menu_KeepParentOnClose(bool dontKeep) { return Menu__Setting([DT_Menu_Settings_KeepParentOnClose, !dontKeep]);  }
global func Menu_ConditionDisableMode(mode) { return Menu__Setting([DT_Menu_Settings_ConditionDisableMode, mode]);}
global func Menu_Vars(array vars) { return Menu__Setting([DT_Menu_Settings_Vars, vars]); }

global func Menu_Callback(array callback, int types, array argBinding)
{
	argBinding = argBinding || [Menu_CallbackArg_Action, Menu_CallbackArg_Symbol, Menu_CallbackArg_MenuObject, Menu_CallbackArg_Args, Menu_CallbackArg_NewSelection, Menu_CallbackArg_OldSelection, Menu_CallbackArg_NewValue, Menu_CallbackArg_OldValue, Menu_CallbackArg_FromSubmenu];
	return [callback, types || Menu_CallbackType_Defaults, argBinding];
}

global func Menu_Entry_Caption(string Caption) { return [DT_Menu_Entry_Caption, Caption]; }
global func Menu_Entry_Callbacks(array Callbacks) { return [DT_Menu_Entry_Callbacks, Callbacks]; }
global func Menu_Entry_Count(int Count) { return [DT_Menu_Entry_Count, Count]; }
global func Menu_Entry_InfoCaption(string InfoCaption) { return [DT_Menu_Entry_InfoCaption, InfoCaption]; }
global func Menu_Entry_Extra(int Extra) { return [DT_Menu_Entry_Extra, Extra]; }
global func Menu_Entry_XPar1(XPar1) { return [DT_Menu_Entry_XPar1, XPar1]; }
global func Menu_Entry_XPar2(XPar2) { return [DT_Menu_Entry_XPar2, XPar2]; }
global func Menu_Entry_Args(Args) { return [DT_Menu_Entry_Args, Args]; }
global func Menu_Entry_Placeholder(bool Placeholder) { return [DT_Menu_Entry_Placeholder, Placeholder]; }
global func Menu_Entry_Symbol(symbol, extra, int color)
{
	if(GetType(symbol) == C4V_Array)
	{
		return [DT_Menu_Entry_Symbol, symbol];
	}
	else
	{
		return [DT_Menu_Entry_Symbol, [symbol, extra, color]];
	}
}
global func Menu_Entry_Condition(callback, int allowDisabledSelection) { return [DT_Menu_Entry_Condition, [callback, allowDisabledSelection]]; }
global func Menu_Entry_VariableCondition(array scopedVar, compare, int disableMode, bool invert, int allowDisabledSelection)
{
	return Menu_Entry_Condition(BindCallback(MN7I->MenuObjectCallback("VariableCondition"), [Bind(scopedVar), Bind(compare), Bind(disableMode), Bind(invert)]), allowDisabledSelection);
}
global func VariableCondition(array scopedVar, compare, int disableMode, bool invert)
{
	var disable = ScopedVar(scopedVar) != compare;
	if(invert)
	{
		disable = !disable;
	}
	if(disable)
	{
		return disableMode;
	}
	else

	{
		return Menu_ConditionReact_Show;
	}
}
global func Menu_Entry_Object(object obj)
{
	return Menu_Combined([Menu_Entry_Symbol(obj), Menu_Entry_Caption(GetName(obj)), Menu_Entry_InfoCaption(GetDesc(obj))]);
}

global func Menu_Entry(array settings)
{
	if(!settings)
	{
		settings = [Menu_Entry_Placeholder(false)];
	}

	var namedArgs = [];
	namedArgs[DT_Menu_Entry_Caption] = "";
	namedArgs[DT_Menu_Entry_Placeholder] = -1;
	MN7I->NamedArgs(settings, namedArgs);
	if(!namedArgs[DT_Menu_Entry_InfoCaption])
	{
		namedArgs[DT_Menu_Entry_Extra] |= C4MN_Add_ForceNoDesc;
	}
	return [DT_Menu_Type_Entry, namedArgs];
}

global func Menu_SubMenu(array entrySettings, array menuEntry_Settings)
{
	var ret = Menu_Entry(entrySettings);
	ret[1][DT_Menu_Entry_Args] = [ret[1][DT_Menu_Entry_Callbacks], ret[1][DT_Menu_Entry_Args], menuEntry_Settings];
	ret[1][DT_Menu_Entry_Callbacks] = [Menu_Callback(MN7I->MenuObjectCallback("SubmenuItemCallback"), Menu_CallbackType_All, [Menu_CallbackArg_Action, Menu_CallbackArg_MenuObject, Menu_CallbackArg_Args, Menu_CallbackArg_All])];
	return ret;
}

global func Menu_Factory(array callbacks, args, array binding)
{
	return [DT_Menu_Type_Factory, [callbacks, args, binding || [Menu_CallbackArg_Args, Menu_CallbackArg_EntryNumber, Menu_CallbackArg_Menu]]];
}

global func Menu_Text(string text, bool allowSelection)
{
	return Menu_Entry([Menu_Entry_Caption(text), Menu_Entry_Placeholder(allowSelection)]);
}

global func Menu_Blank(bool allowSelection)
{
	return Menu_Entry([Menu_Entry_Placeholder(allowSelection)]);
}

func DeclineAcceptBack(string caption, symbol, string callback, array settings)
{
	var ret = Menu_Entry([Menu_Entry_Caption(caption), Menu_Combined(settings || [])]);
	ret[1][DT_Menu_Entry_Args] = [ret[1][DT_Menu_Entry_Callbacks], ret[1][DT_Menu_Entry_Args]];
	ret[1][DT_Menu_Entry_Callbacks] = Menu_Entry_Callbacks([Menu_Callback(MN7I->MenuObjectCallback(callback), Menu_CallbackType_All, [Menu_CallbackArg_Action, Menu_CallbackArg_Args, Menu_CallbackArg_All])])[1];
	ExtraSymbol(ret[1][DT_Menu_Entry_Caption], ret[1][DT_Menu_Entry_Symbol], symbol);
	return ret;
}

global func Menu_Decline(array settings)
{
	return MN7I->DeclineAcceptBack("$Decline$", [MN7I, 2], "DeclineAcceptCommand", settings);
}

global func Menu_Accept(array settings)
{
	return MN7I->DeclineAcceptBack("$Accept$", [MN7I, 1], "DeclineAcceptCommand", settings);
}

global func Menu_Back(array settings)
{
	return MN7I->DeclineAcceptBack("$Back$", [MN7I, 5], "BackCommand", settings);
}

global func Menu_Adaptor_Type(int Type) { return [DT_Menu_Adaptor_Type, Type]; }
global func Menu_Adaptor_Variable(array Variable) { return [DT_Menu_Adaptor_Variable, Variable]; }
global func Menu_Adaptor_Callbacks(array Callbacks) { return [DT_Menu_Adaptor_Callbacks, Callbacks]; }
global func Menu_Adaptor_MessageBoardText(string MessageBoardText) { return [DT_Menu_Adaptor_MessageBoardText, MessageBoardText]; }
global func Menu_Adaptor_WrapAround(bool WrapAround) { return [DT_Menu_Adaptor_WrapAround, WrapAround]; }
global func Menu_Adaptor_EnumSubmenuSymbol(id EnumSubmenuSymbol) { return [DT_Menu_Adaptor_EnumSubmenuSymbol, EnumSubmenuSymbol]; }
global func Menu_Adaptor_EnumAllowUnknown(bool EnumAllowUnknown) { return [DT_Menu_Adaptor_EnumAllowUnknown, EnumAllowUnknown]; }
global func Menu_Adaptor_EnumInline(bool EnumInline) { return [DT_Menu_Adaptor_EnumInline, EnumInline]; }
global func Menu_Adaptor_EnumSubmenu(int callbackType) { return [DT_Menu_Adaptor_EnumSubmenu, callbackType]; }
global func Menu_Adaptor_Limits(min, max, args)
{
	return [DT_Menu_Adaptor_Limits, [min, max, args]];
}
global func Menu_Adaptor_StepSize(int step, force) { return [DT_Menu_Adaptor_StepSize, [step, force]]; }
global func Menu_Adaptor_Enum(array enumVals, array layout, bool valuesAsSeparateLists)
{
	MN7I->AdaptorLayout(layout, enumVals, valuesAsSeparateLists);
	return Menu_Combined([Menu_Adaptor_Type(Menu_AdaptorType_Enum), [DT_Menu_Adaptor_LayoutVals, [enumVals, layout]]]);
}
global func Menu_Adaptor_BitField(array fieldVals, array layout, bool valuesAsSeparateLists, bool bitPositionAsValue)
{
	MN7I->AdaptorLayout(layout, fieldVals, valuesAsSeparateLists);
	if(bitPositionAsValue)
	{
		var valuePos = layout[Menu_Layout__ValuePos] - 1;
		for(var i = 0; i < GetLength(fieldVals); ++i)
		{
			fieldVals[i][valuePos] = 1 << fieldVals[i][valuePos];
		}
	}
	return Menu_Combined([Menu_Adaptor_Type(Menu_AdaptorType_BitField), [DT_Menu_Adaptor_LayoutVals, [fieldVals, layout]]]);
}
global func Menu_Adaptor_NoEmptyString() { return [DT_Menu_Adaptor_NoEmptyString, true]; }
global func Menu_Adaptor_EnumSubmenuCaption(string menuCaption, string entryCaption)
{
	return [DT_Menu_Adaptor_EnumSubmenuCaption, [menuCaption, entryCaption]];
}
global func Menu_Adaptor_Boolean() { return Menu_Adaptor_Type(Menu_AdaptorType_Boolean); }
global func Menu_Adaptor_Integer() { return Menu_Adaptor_Type(Menu_AdaptorType_Integer); }
global func Menu_Adaptor_String() { return Menu_Adaptor_Type(Menu_AdaptorType_String); }
global func Menu_Adaptor_ID() { return Menu_Adaptor_Type(Menu_AdaptorType_ID); }

func AdaptorLayout(array& layout, array& vals, bool valuesAsSeparateLists)
{
	layout = layout || [Menu_Layout_Value | Menu_Layout_Caption];
	var layoutMap = [];
	var index = 1;
	for(var val in layout)
	{
		var noFlag = val & Menu_Layout__NoFlagMask;

		if(noFlag)
		{
			layoutMap[noFlag] = index;
		}

		if(val & Menu_Layout_Caption)
		{
			layoutMap[Menu_Layout__CaptionPos] = index;
		}

		if(val & Menu_Layout_Value)
		{
			layoutMap[Menu_Layout__ValuePos] = index;
		}

// 		if(val & Menu_Layout_InputValue) TODO
// 		{
// 			layoutMap[Menu_Layout__InputValuePos] = index;
// 		}

		++index;
	}

	layout = layoutMap;

	if(valuesAsSeparateLists)
	{
		var tempVals = vals;
		var vals = [];

		for(var i = 0; i < GetLength(tempVals[0]); ++i)
		{
			vals[i] = [];

			for(var j = 0; j < GetLength(tempVals); ++j)
			{
				vals[i][j] = tempVals[j][i];
			}
		}
	}
}

global func Menu_Adaptor(array entrySettings, array adaptorSettings)
{
	var adaptorArgs = [];

	adaptorArgs[DT_Menu_Adaptor_WrapAround] = -1;
	adaptorArgs[DT_Menu_Adaptor_EnumSubmenu] = Menu_CallbackType_Special2;

	MN7I->NamedArgs(adaptorSettings, adaptorArgs);

	if(adaptorArgs[DT_Menu_Adaptor_WrapAround] == -1)
	{
				if(adaptorArgs[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Integer)
		{
			adaptorArgs[DT_Menu_Adaptor_WrapAround] = false;
		}
		else if(adaptorArgs[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Enum)
		{
			adaptorArgs[DT_Menu_Adaptor_WrapAround] = true;
		}
	}

	return Menu_Factory([MN7I->MenuObjectCallback("AdaptorFactory")], [Menu_Entry(entrySettings)[1], adaptorArgs, entrySettings]);
}

func EnumValPos(array enumVals, array layout, val, bool allowUnknown)
{
	for(var i = 0; i < GetLength(enumVals); ++i)
	{
		if(enumVals[i][layout[Menu_Layout__ValuePos] - 1] == val)
		{
			return i;
		}
	}
	return -1;
}

func BooleanToggleCaption(bool val, string& caption, &symbol)
{
	val = !!val;
	ExtraSymbol(caption, symbol, [MN7I, 2 - val, !val && RGB(128, 128, 128)]);
}

func InlineSymbol(string& caption, symbol)
{
	if(symbol[2])
	{
		caption = Format("<c %x>{{%i:%d}}</c> %s", symbol[2], symbol[0], symbol[1], caption);
	}
	else
	{
		caption = Format("{{%i:%d}} %s", symbol[0], symbol[1], caption);
	}
}

func ExtraSymbol(string& caption, &symbol, extraSymbol)
{
	if(GetType(extraSymbol) == C4V_C4ID)
	{
		extraSymbol = [extraSymbol];
	}

	if(symbol && extraSymbol && GetType(extraSymbol[0]) == C4V_C4ID)
	{
		InlineSymbol(caption, extraSymbol);
	}
	else
	{
		symbol = extraSymbol;
	}
}

func EnumEntrySettings(string& caption, &symbol, string& infoCaption, int index, array args, array entry)
{
	var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
	var layout = layoutVals[1];
	layoutVals = layoutVals[0];

	caption = entry[DT_Menu_Entry_Caption];
	if(layout[Menu_Layout__CaptionPos])
	{
		caption = Format(caption, layoutVals[index][layout[Menu_Layout__CaptionPos] - 1]);
	}

	if(layout[Menu_Layout_Symbol])
	{
		ExtraSymbol(caption, symbol, layoutVals[index][layout[Menu_Layout_Symbol] - 1]);
	}

	if(layout[Menu_Layout_InfoCaption])
	{
		infoCaption = Format(infoCaption, layoutVals[index][layout[Menu_Layout_InfoCaption] - 1]);
	}
}

func AdaptorGetLimits(array limits)
{
	var ret = CreateArray(2);
	if(!limits)
	{
		limits = [Menu_Adaptor_Limits_Min, Menu_Adaptor_Limits_Max];
	}

	for(var i = 0; i < 2; ++i)
	{
		if(!limits[i] || GetType(limits[i]) == C4V_Int)
		{
			ret[i] = limits[i];
		}
		else
		{
			ret[i] = Call(limits[i], limits[3]);
		}
	}

	return ret;
}

func AdaptorFactory(args, int entryIndex)
{
	var origArgs = args;
	var entry = args[0];
	var entrySettings = args[2];
	args = args[1];
	var caption = entry[DT_Menu_Entry_Caption];
	var infoCaption = entry[DT_Menu_Entry_InfoCaption];
	var symbol = entry[DT_Menu_Entry_Symbol];
	var val = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var defaultMsgboardText = "$EnterValue$";

	var retSubmenu;

	args[DT_Menu_Adaptor_Args] = entry[DT_Menu_Entry_Args];
	args[DT_Menu_Adaptor_EntryIndex] = entryIndex;
	args[DT_Menu_Adaptor_Callbacks] = args[DT_Menu_Adaptor_Callbacks] || [];
	if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Boolean)
	{
		BooleanToggleCaption(val, caption, symbol);
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_String)
	{
		caption = Format(entry[DT_Menu_Entry_Caption], val);
		defaultMsgboardText = "$EnterText$";
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Integer)
	{
		var limits = AdaptorGetLimits(args[DT_Menu_Adaptor_Limits]), max, min;
		var wrapAround = args[DT_Menu_Adaptor_WrapAround];
		if(limits && !wrapAround)
		{
			if(val >= limits[1])
			{
				max = true;
			}
			if(val <= limits[0])
			{
				min = true;
			}
		}
		caption = Format("%s %s", Format(entry[DT_Menu_Entry_Caption], val), ["{{MN7I:4}}", "<c 808080>{{MN7I:4}}</c>"][min]);
		ExtraSymbol(caption, symbol, [MN7I, 3, max && RGB(128, 128, 128)]);
		defaultMsgboardText = "$EnterNumber$";
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_ID)
	{
		caption = Format(entry[DT_Menu_Entry_Caption], val && GetName(0, val) || "");
		if(val)
		{
			ExtraSymbol(caption, symbol, val);
		}
		defaultMsgboardText = "$EnterIDOrName$";
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Enum)
	{
		if(args[DT_Menu_Adaptor_EnumInline])
		{
			return AdaptorEnumSubmenuFactory([args, entry]);
		}

		var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
		var layout = layoutVals[1];
		layoutVals = layoutVals[0];

		var index = EnumValPos(layoutVals, layout, val, args[DT_Menu_Adaptor_EnumAllowUnknown]);

		if(index == -1)
		{
			if(!args[DT_Menu_Adaptor_EnumAllowUnknown])
			{
				ScopedVar(args[DT_Menu_Adaptor_Variable]) = layoutVals[0][layout[Menu_Layout__ValuePos] - 1];
			}
			index = 0;
		}

		var submenuSymbol = symbol;

		EnumEntrySettings(caption, symbol, infoCaption, index, args, entry);

		if(args[DT_Menu_Adaptor_EnumSubmenu] != Menu_CallbackType_None)
		{
			args[DT_Menu_Adaptor_MessageBoardText] = args[DT_Menu_Adaptor_MessageBoardText] || defaultMsgboardText;

			retSubmenu = [Menu_Factory([MenuObjectCallback("AdaptorEnumSubmenuFactory")], [args, entry])];
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_BitField)
	{
		return AdaptorBitFieldItemsFactory(origArgs);
	}
	args[DT_Menu_Adaptor_MessageBoardText] = args[DT_Menu_Adaptor_MessageBoardText] || defaultMsgboardText;
	if(!retSubmenu)
	{
		return [Menu_Entry([Menu_Combined(entrySettings), Menu_Entry_Caption(caption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorCommand"), Menu_CallbackType_All, [Menu_CallbackArg_Action, Menu_CallbackArg_MenuObject, Menu_CallbackArg_Args, Menu_CallbackArg_All])]), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Args(args)])];
	}
	else
	{
		return [Menu_SubMenu([Menu_Combined(entrySettings), Menu_Entry_Caption(caption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorCommand"), Menu_CallbackType_All, [Menu_CallbackArg_Action, Menu_CallbackArg_MenuObject, Menu_CallbackArg_Args, Menu_CallbackArg_All])]), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Args(args)], retSubmenu)];
	}
}

func AdaptorEnumSubmenuFactory(array args)
{
	var entry = args[1];
	args = args[0];
	var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
	var layout = layoutVals[1];
	layoutVals = layoutVals[0];

	var submenuCaption = args[DT_Menu_Adaptor_EnumSubmenuCaption];
	var submenuSymbol = [];

	if(submenuCaption && submenuCaption[0])
	{
		entry[DT_Menu_Entry_Caption] = submenuCaption[0];
	}

	var index = EnumValPos(layoutVals, layout, ScopedVar(args[DT_Menu_Adaptor_Variable]), args[DT_Menu_Adaptor_EnumAllowUnknown]);
	var symbol, infoCaption;
	EnumEntrySettings(submenuCaption, symbol, infoCaption, index, args, entry);

	var ret;
	if(args[DT_Menu_Adaptor_EnumInline])
	{
		ret = [];
	}
	else
	{
		ret = [
			Menu_Selection(index),
			Menu_KeepParentOnClose(),
			Menu_DontKeepOpen(),
			Menu_Caption(submenuCaption)
		];
	}

	if(args[DT_Menu_Adaptor_EnumSubmenuSymbol])
	{
		submenuSymbol = [args[DT_Menu_Adaptor_EnumSubmenuSymbol]];
	}
	else if(!submenuSymbol && symbol && GetType(symbol[0]) == C4V_C4ID)
	{
		submenuSymbol = symbol;
	}

	if(submenuSymbol && GetType(submenuSymbol[0]) == C4V_C4ID)
	{
		ArrayAppend(ret, Menu_Symbol(submenuSymbol[0]));
	}

	var caption;

	var submenuCaption = args[DT_Menu_Adaptor_EnumSubmenuCaption];
	if(submenuCaption && submenuCaption[1])
	{
		entry[DT_Menu_Entry_Caption] = submenuCaption[1];
	}

	for(var i = 0; i < GetLength(layoutVals); ++i)
	{
		symbol = 0;
		EnumEntrySettings(caption, symbol, infoCaption, i, args, entry);
		if(args[DT_Menu_Adaptor_EnumInline])
		{
			BooleanToggleCaption(i == index, caption, symbol);
		}
		ArrayAppend(ret, Menu_Entry([Menu_Entry_Caption(caption), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorEnumSubmenuItem"), Menu_CallbackType_Defaults, [Menu_CallbackArg_Args, Menu_CallbackArg_All])]), Menu_Entry_Args([i, args])]));
	}

	return ret;
}

func AdaptorEnumSubmenuItem(args, array allArgs)
{
	var index = args[0];
	args = args[1];

	var val = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var oldVal = val;

	var enumVals = args[DT_Menu_Adaptor_LayoutVals];
	var layout = enumVals[1];
	enumVals = enumVals[0];

	ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = enumVals[index][layout[Menu_Layout__ValuePos] - 1];

	allArgs[Menu_CallbackArg_Args] = args[DT_Menu_Adaptor_Args];
	allArgs[Menu_CallbackArg_FromSubmenu] = true;

	var reaction = AdaptorCommandCallChangedCallback(args[DT_Menu_Adaptor_Callbacks], val, oldVal, allArgs);
	if(reaction != Menu_React_None)
	{
		return reaction;
	}

	if(args[DT_Menu_Adaptor_EnumInline])
	{
		return Menu_React_Refresh;
	}

	return Menu_React_Back;
}

func AdaptorBitFieldItemsFactory(args)
{
	var entry = args[0];
	var entrySettings = args[2];
	args = args[1];

	var caption = entry[DT_Menu_Entry_Caption];
	var infoCaption = entry[DT_Menu_Entry_InfoCaption];
	var symbol = entry[DT_Menu_Entry_Symbol];
	var fieldValue = ScopedVar(args[DT_Menu_Adaptor_Variable]);

	var layoutVals = args[DT_Menu_Adaptor_LayoutVals];
	var layout = layoutVals[1];
	layoutVals = layoutVals[0];

	var ret = [];

	for(var val in layoutVals)
	{
		var mask = val[layout[Menu_Layout__ValuePos] - 1];
		caption = entry[DT_Menu_Entry_Caption] || "%s";
		if(layout[Menu_Layout__CaptionPos])
		{
			caption = Format(caption, val[layout[Menu_Layout__CaptionPos] - 1]);
		}

		symbol = entry[DT_Menu_Entry_Symbol];
		BooleanToggleCaption((fieldValue & mask) == mask, caption, symbol);
		if(layout[Menu_Layout_Symbol])
		{
			ExtraSymbol(caption, symbol, val[layout[Menu_Layout_Symbol] - 1]);
		}

		if(layout[Menu_Layout_InfoCaption])
		{
			infoCaption = Format(infoCaption, val[layout[Menu_Layout_InfoCaption] - 1]);
		}

		args[DT_Menu_Adaptor_Mask] = mask;

		ArrayAppend(ret, Menu_Entry([Menu_Combined(entrySettings), Menu_Entry_Caption(caption), Menu_Entry_Callbacks([Menu_Callback(MenuObjectCallback("AdaptorCommand"), Menu_CallbackType_All, [Menu_CallbackArg_Action, Menu_CallbackArg_MenuObject, Menu_CallbackArg_Args, Menu_CallbackArg_All])]), Menu_Entry_Symbol(symbol), Menu_Entry_InfoCaption(infoCaption), Menu_Entry_Args(args)]));
	}

	return ret;
}

func WrapOrBind(int val, array limits, bool wrap)
{
	if(!limits)
	{
		return val;
	}

	var min = limits[0];
	var max = limits[1];

	if(val < min)
	{
		if(wrap)
		{
			return max;
		}
		else
		{
			return min;
		}
	}
	else if(val > max)
	{
		if(wrap)
		{
			return min;
		}
		else
		{
			return max;
		}
	}
	else
	{
		return val;
	}
}

func AdaptorCommandCallChangedCallback(callbacks, val, oldVal, array allArgs)
{
	allArgs[Menu_CallbackArg_Action] = Menu_CallbackType_ValueChanged;
	allArgs[Menu_CallbackArg_NewValue] = val;
	allArgs[Menu_CallbackArg_OldValue] = oldVal;

	return CallCallbacks(callbacks, Menu_CallbackType_ValueChanged, allArgs, ...);
}

func AdaptorCommand(int action, object obj, args, array allArgs)
{
	var val = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var oldVal = val;

	allArgs[Menu_CallbackArg_Args] = args[DT_Menu_Adaptor_Args];

	var reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], action, allArgs, Menu_React_Refresh, true);


	if(reaction != Menu_React_Refresh)
	{
		return reaction;
	}
	if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Boolean)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = !val;
			reaction = AdaptorCommandCallChangedCallback(args[DT_Menu_Adaptor_Callbacks], val, oldVal, allArgs);
			if(reaction != Menu_React_None)
			{
				return reaction;
			}
		}
		else
		{
			return Menu_React_KeepOpen;
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Integer)
	{
		var limits = AdaptorGetLimits(args[DT_Menu_Adaptor_Limits]);
		var wrapAround = args[DT_Menu_Adaptor_WrapAround];
		var step = args[DT_Menu_Adaptor_StepSize];
		var stepSize = 1;
		if(step)
		{
			stepSize = step[0];
		}
		if(action == Menu_CallbackType_Special2)
		{
			if(msgBoardMode == 0)
			{
				msgBoardMode = Menu_AdaptorType_Integer + 1;
				msgBoardEntry = args[DT_Menu_Adaptor_EntryIndex];
				CallMessageBoard(this, false, args[DT_Menu_Adaptor_MessageBoardText], GetOwner(obj));
			}
			return Menu_React_KeepOpen;
		}
		else if(action == Menu_CallbackType_Normal)
		{
			val += stepSize;
		}
		else if(action == Menu_CallbackType_Close)
		{
			val -= stepSize;
		}
		else
		{
			return Menu_React_KeepOpen;
		}

		val = WrapOrBind(val, limits, wrapAround);

		if(val != oldVal)
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = val;
			reaction = AdaptorCommandCallChangedCallback(args[DT_Menu_Adaptor_Callbacks], val, oldVal, allArgs);
			if(reaction != Menu_React_None)
			{
				return reaction;
			}
		}
		else
		{
			return Menu_React_KeepOpen;
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_String)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			if(msgBoardMode == 0)
			{
				msgBoardMode = Menu_AdaptorType_String + 1;
				msgBoardEntry = args[DT_Menu_Adaptor_EntryIndex];
				CallMessageBoard(this, false, args[DT_Menu_Adaptor_MessageBoardText], GetOwner(obj));
			}
		}
		if(action == Menu_CallbackType_Close)
		{
			return Menu_React_None;
		}
		else
		{
			return Menu_React_KeepOpen;
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_ID)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			if(msgBoardMode == 0)
			{
				msgBoardMode = Menu_AdaptorType_ID + 1;
				msgBoardEntry = args[DT_Menu_Adaptor_EntryIndex];
				CallMessageBoard(this, false, args[DT_Menu_Adaptor_MessageBoardText], GetOwner(obj));
			}
		}
		return Menu_React_KeepOpen;
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_Enum)
	{
		if(GetType(args[DT_Menu_Adaptor_EnumSubmenu]) == C4V_Bool)
		{
			if(action & Menu_CallbackType_Defaults)
			{
				return Menu_React_ShowSubmenu;
			}
			else
			{
				return Menu_React_None;
			}
		}

		if(args[DT_Menu_Adaptor_EnumSubmenu] & action)
		{
			return Menu_React_ShowSubmenu;
		}

		var enumVals = args[DT_Menu_Adaptor_LayoutVals];
		var layout = enumVals[1];
		enumVals = enumVals[0];

		var index = EnumValPos(enumVals, layout, val, args[DT_Menu_Adaptor_EnumAllowUnknown]);
		var wrapAround = args[DT_Menu_Adaptor_WrapAround];

		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			++index;
		}
		else if(action == Menu_CallbackType_Close)
		{
			--index;
		}
		else
		{
			return Menu_React_None;
		}

		index = WrapOrBind(index, [0, GetLength(enumVals) - 1], wrapAround);

		ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = enumVals[index][layout[Menu_Layout__ValuePos] - 1];
		reaction = AdaptorCommandCallChangedCallback(args[DT_Menu_Adaptor_Callbacks], val, oldVal, allArgs);
		if(reaction != Menu_React_None)
		{
			return reaction;
		}
	}
	else if(args[DT_Menu_Adaptor_Type] == Menu_AdaptorType_BitField)
	{
		if(action & (Menu_CallbackType_Normal | Menu_CallbackType_Special2))
		{
			var mask = args[DT_Menu_Adaptor_Mask];
			if((val & mask) == mask)
			{
				val &= ~mask;
			}
			else
			{
				val |= mask;
			}

			ScopedVar(args[DT_Menu_Adaptor_Variable]) = val;
			reaction = AdaptorCommandCallChangedCallback(args[DT_Menu_Adaptor_Callbacks], val, oldVal, allArgs);
			if(reaction != Menu_React_None)
			{
				return reaction;
			}
		}
		else
		{
			return Menu_React_KeepOpen;
		}
	}

	return Menu_React_Refresh;
}

func InputCallback(string input, int plr)
{
	var entry = entries[msgBoardEntry];
	var args = entry[DT_Menu_Entry_Args];
	var callbackArgs = args[DT_Menu_Adaptor_Args];
	var oldVal = ScopedVar(args[DT_Menu_Adaptor_Variable]);
	var val = input;
	if(msgBoardMode - 1 == Menu_AdaptorType_Integer)
	{
		var int = ParseInt(input);
		var limits = AdaptorGetLimits(args[DT_Menu_Adaptor_Limits]);
		var step = args[DT_Menu_Adaptor_StepSize];
		if(GetType(int) == C4V_Int || GetType(int) == C4V_Any)
		{
			if(step && step[1])
			{
				var s = step[0];
				if(GetType(step[1]) == C4V_Int)
				{
					s = step[1];
				}
				int = ((int + s / 2) / s) * s;
			}
			if(limits)
			{
				int = BoundBy(int, limits[0], limits[1]);
			}
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = val = int;
		}
		else
		{
			val = oldVal;
		}
	}
	else if(msgBoardMode - 1 == Menu_AdaptorType_String)
	{
		if(args[DT_Menu_Adaptor_NoEmptyString] && (!input || input == ""))
		{
			val = oldVal;
		}
		else
		{
			ScopedVar(args[DT_Menu_Adaptor_Variable]) = input;
		}
	}
	else if(msgBoardMode - 1 == Menu_AdaptorType_ID)
	{
		val = GetIDByName(input); // WARNING: desyncs between clients with different languages
		if(!val && GetLength(input) == 4) val = C4Id(input);
		if(!GetName(0, val)) val = 0;
		ScopedVar(args[DT_Menu_Adaptor_Variable]) = val;
	}
	msgBoardMode = 0;
	if(val != oldVal)
	{
		var reaction = CallCallbacks(args[DT_Menu_Adaptor_Callbacks], Menu_CallbackType_ValueChanged, [Menu_CallbackType_ValueChanged, entry[DT_Menu_Entry_Symbol], settings[DT_Menu_Settings_Object], callbackArgs, 0, 0, val, oldVal]);
		if(reaction != Menu_React_None)
		{
			return React(reaction, msgBoardEntry);
		}
	}
	Refresh(msgBoardEntry);
}

global func Menu_Combined(array combined) { return [DT_Menu_Combined, combined]; }

global func CreateNewMenu(array menu, inheritSettings, object parentMenu)
{
	var settings = inheritSettings;

	if(GetType(settings) != C4V_Array) settings = [];
	settings[DT_Menu_Settings_Style] &= ~C4MN_Style_EqualItemHeight; // EqualItemHeight can't be inherited
	settings[DT_Menu_Settings_Selection] = 0; // Selection can't be inherited
	settings[DT_Menu_Settings_Callbacks] = 0; // Global callbacks can't be inherited (maybe filter callbacks)

	settings[DT_Menu_Settings_Parent] = parentMenu;

	var entries = [];

	MN7I->UncombineAndDistinguish(menu, settings, entries);

	var menuObj = CreateObject(MN7I);

	menuObj->Create(settings, entries);

	return menuObj;
}

func NamedArg(array namedArg, array &args)
{
	args[namedArg[0]] = namedArg[1];
}

func UncombineAndDistinguish(array combined, array &settings, array &entries)
{
	for(var val in combined)
	{
		if(val[0] == DT_Menu_Type_Setting)
		{
			if((val[1][0] == DT_Menu_Settings_Style && val[1][1] == C4MN_Style_EqualItemHeight) || settings[DT_Menu_Settings_Style] == C4MN_Style_EqualItemHeight)
			{
				settings[DT_Menu_Settings_Style] |= val[1][1];
			}
			else
			{
				NamedArg(val[1], settings);
			}
		}
		else if(val[0] == DT_Menu_Type_Entry || val[0] == DT_Menu_Type_Factory)
		{
			entries[GetLength(entries)] = val;
		}
		else if(val[0] == DT_Menu_Combined)
		{
			UncombineAndDistinguish(val[1], settings, entries);
		}
	}
}

func NamedArgs(array namedArgs, array& args)
{
	for(var arg in namedArgs)
	{
		if(arg[0] == DT_Menu_Combined)
		{
			NamedArgs(arg[1], args);
		}
		else
		{
			NamedArg(arg, args);
		}
	}
}

func DeclineAcceptBackCommand(int action, args, int defaultAction, array allArgs)
{
	if(args[0])
	{
		allArgs[Menu_CallbackArg_Args] = args[1];
		var reaction = CallCallbacks(args[0], action, allArgs);
		if(reaction != Menu_React_None)
		{
			return reaction;
		}
	}

	if(action & Menu_CallbackType_Defaults)
	{
		return defaultAction;
	}
	else
	{
		return Menu_React_None;
	}
}

func DeclineAcceptCommand(int action, args, array allArgs)
{
	return DeclineAcceptBackCommand(action, args, Menu_React_Close, allArgs);
}

func BackCommand(int action, args, array allArgs)
{
	return DeclineAcceptBackCommand(action, args, Menu_React_Back, allArgs);
}

func MenuObjectCallback(string name)
{
	return [CallbackTarget_Scenario - 1, name];
}

func CallCustom(callback, args)
{
	if(GetType(callback) == C4V_Array && GetLength(callback) == 2 && callback[0] == CallbackTarget_Scenario - 1)
	{
		return CallA(ObjectCallback(callback[1], this), args, ...);
	}
	else
	{
		return _inherited(callback, args, ...);
	}
}

func CustomScopedVar(array variable)
{
	if(variable && variable[0] == DT_Menu_MenuVar)
	{
		return ArrayVar(variable[1], LocalVar("vars"));
	}
	else
	{
		return _inherited(variable, ...);
	}
}

func CheckCustomScopedVar(array variable)
{
	if(variable && variable[0] == DT_Menu_MenuVar && ((GetType(variable[1]) == C4V_Int && variable[1] > 0) || variable[1] == 0))
	{
		return true;
	}
	else
	{
		return _inherited(variable, ...);
	}
}

func Update()
{
	return Refresh(currentSelection);
}

func GetSelection()
{
	return currentSelection;
}

func GetObject()
{
	return settings[DT_Menu_Settings_Object];
}

func CreateSymbolDummy()
{
	return CreateContents(DT_Menu_SymbolDummy);
}