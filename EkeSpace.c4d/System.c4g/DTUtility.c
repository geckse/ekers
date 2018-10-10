#strict 2

global func Isolate(object obj) // Puts the object in its own layer to prevent interaction
{
	obj || obj = this;
	return obj->SetObjectLayer(obj);
}

global func GetIndexOf2(val, array arr) // Because GetIndexOf doesn't find Format("%c", GetChar("a", 0)) in ["a"]
{
	var i = 0;
	for(var value in arr)
	{
		if(val == value) return i;
		++i;
	}
	return -1;
}

global func Serialize(value)
{
	if(GetType(value) == C4V_Array)
	{
		var first = true;
		var ret = "[";
		for(var val in value)
		{
			if(first)
			{
				first = false;
			}
			else
			{
				ret = Format("%s,", ret);
			}
			ret = Format("%s%s", ret, Serialize(val));
		}
		return Format("%s]", ret);
	}
	else if(GetType(value) == C4V_Bool) if(value) return "true"; else return "false";
	else if(GetType(value) == C4V_C4ID) return Format("%i", value);
	else if(GetType(value) == C4V_C4Object) return Format("Object(%d)", ObjectNumber(value));
	else if(GetType(value) == C4V_Int || GetType(value) == C4V_Any) return Format("%d", value);
	else if(GetType(value) == C4V_String) return Format("\"%s\"", EscapeString(value));
}

global func EscapeString(string value)
{
	var ret = "";
	for(var i = 0; i < GetLength(value); ++i)
	{
		var c = GetChar(value, i);
		if(c == 34) // "
		{
			ret = Format("%s\\\"", ret);
		}
		else if(c == 92) // \
		{
			ret = Format("%s\\\\", ret);
		}
		else
		{
			ret = Format("%s%c", ret, c);
		}
	}
	return ret;
}

global func CreateEnum(string prefix, array enum)
{
	var log = Format("%c// This enum was created with CreateEnum(%s, %s);%c", 10, Serialize(prefix), Serialize(enum), 10);
	var switch = "";

	for(var i = 0; i < GetLength(enum); ++i)
	{
		log = Format("%s%cstatic const %s%s = %d;", log, 10, prefix, enum[i], i);

		if(switch == "")
		{
			switch = Format("if(switchval == %s%s)%c{%c%c}%c", prefix, enum[i], 10, 10, 10, 10);
		}
		else
		{
			switch = Format("%selse if(switchval == %s%s)%c{%c%c}%c", switch, prefix, enum[i], 10, 10, 10, 10);
		}
	}

	Log("%s%c%c// Template if-structure - replace switchval with the value to compare.%c%c%s", log, 10, 10, 10, 10, switch);
}

global func CreateBitField(string prefix, array flags)
{
	if(GetLength(flags) > 32)
	{
		FatalError("CreateBitField: A bitfield can only have a maximum of up to 32 flags.");
		return;
	}

	var log = Format("%c// This bitfield was created with CreateBitField(%s, %s);%c", 10, Serialize(prefix), Serialize(flags), 10);

	for(var i = 0, j = 1; i < GetLength(flags); ++i)
	{
		log = Format("%s%cstatic const %s%s = %d;", log, 10, prefix, flags[i], j);
		j = j << 1;
	}

	Log("%s%c%c", log, 10, 10);
}

// pos >= 0 => begin at pos | pos < 0 => begin at GetLength(string) - pos
// count = 0 => replace all | count > 0 replace a maximum of count occurences from starting from pos

global func Lowercase(int c)
{
	if((c >= 65 && c <= 90) || (c >= 192 && c <= 214) || (c >= 216 && c <= 221)) return c + 32;
	else return c;
}

global func StringLowercase(string string)
{
	var ret = "";
	for(var i = 0; i < GetLength(string); ++i)
	{
		ret = Format("%s%c", ret, Lowercase(GetChar(string, i)));
	}
	return ret;
}

global func MultiStringLowercase(array strings)
{
	var ret = [];
	for(var string in strings)
	{
		ret[GetLength(ret)] = StringLowercase(string);
	}
	return ret;
}

global func CaseInsensitive(int c, bool caseSensitive) // TODO
{
	if(caseSensitive) return c;
	else return Lowercase(c);
}

global func StringConcatenate(array strings)
{
	var ret = strings[0];

	for(var i = 1; i < GetLength(strings); ++i)
	{
		ret = Format("%s%s", ret, strings[i]);
	}

	return ret;
}

global func MultiStringReplace(find, strings, replace, bool caseInsensitive, int count, int pos, int maxpos)
{
	var returnString = false;
	if(GetType(strings) == C4V_String)
	{
		strings = [strings];
		returnString = true;
	}
	else if(GetType(strings) != C4V_Array) return strings;
	if(GetType(find) == C4V_String) find = [find];
	else if(GetType(find) != C4V_Array) return strings;
	if(GetType(replace) == C4V_String) replace = [find];
	else if(GetType(replace) != C4V_Array) return strings;

	var ret = [];

	for(var i = 0; i < GetLength(strings); ++i)
	{
		ret[i] = strings[i];
		for(var j = 0; j < GetLength(find); ++j)
		{
			ret[i] = StringReplace(find[j], ret[i], replace[j % GetLength(replace)], caseInsensitive, count, pos, maxpos);
		}
	}

	if(returnString) return ret[0];
	else return ret;
}

global func StringReplace(string find, string string, string replace, bool caseInsensitive, int count, int pos, int maxpos)
{
	if(GetLength(find) == 0 || GetLength(string) == 0) return string;
	var ret = "";
	if(pos < 0) pos = GetLength() - pos;
	if(maxpos < 0) maxpos = GetLength(string) - pos;
	if(maxpos == 0) maxpos = GetLength(string);
	if(pos < 0 || pos > GetLength(string) || maxpos < 0 || maxpos > GetLength(string) || count < 0) return string;
	if(count == 0) count = -1;

	for(var i = 0; i < pos; ++i)
	{
		ret = Format("%s%c", ret, GetChar(string, i));
	}

	var match = 0;

	var i;

	for(i = pos; i + GetLength(find) - match - 1 < maxpos && count != 0; ++i)
	{
		var c = GetChar(string, i);
		if(CaseInsensitive(c, !caseInsensitive) == CaseInsensitive(GetChar(find, match), !caseInsensitive))
		{
			if(++match == GetLength(find))
			{
				ret = StringConcatenate([ret, replace]);
				match = 0;
				--count;
			}
		}
		else
		{
			if(match != 0)
			{
				for(var j = i - match; j < i; ++j)
				{
					ret = Format("%s%c", ret, GetChar(string, j));
				}
			}
			match = 0;
			ret = Format("%s%c", ret, GetChar(string, i));
		}
	}

	for(i -= match; i < GetLength(string); ++i)
	{
		ret = Format("%s%c", ret, GetChar(string, i));
	}

	return ret;
}

global func StringReplaceMulti(string find, string string, array replace)
{
	var ret = [];
	for(var rep in replace)
	{
		ret[GetLength(ret)] = StringReplace(find, string, rep);
	}
	return ret;
}

global func MultiStringReplaceMulti(string string, array findReplace)
{
	var ret = [];

	for(var j = 0; j < GetLength(findReplace[0][1]); ++j)
	{
		var part = string;
		for(var i = 0; i < GetLength(findReplace); ++i)
		{
			part = StringReplace(findReplace[i][0], part, findReplace[i][1][j]);
		}
		ret[j] = part;
	}

	return ret;
}

global func GetMapValue(key, array map, default)
{
	for(var val in map)
	{
		if(val[0] == key) return val;
	}
	return default;
}

global func GetIDByName(string name, int category) // WARNING: desyncs between clients with different languages
{
	var i, id;
	while(id = GetDefinition(i++, category))
	{
		if(GetName(0, id) == name) return id;
	}
	return 0;
}

global func GetIDsByName(string name, int category) // WARNING: desyncs between clients with different languages
{
	var i, id, ret = [];
	while(id = GetDefinition(i++, category))
	{
		if(GetName(0, id) == name)
		{
			ret[GetLength(ret)] = id;
		}
	}
	return ret;
}

global func ArrayConcatenate(array arrays)
{
	var ret = [];
	for(var arr in arrays)
	{
		for(var val in arr)
		{
			ret[GetLength(ret)] = val;
		}
	}
	return ret;
}

global func SetPlrExtraDataString(int plr, string name, string data)
{
	var part = 0;
	var i;
	for(i = 0; i < GetLength(data); ++i)
	{
		var c = GetChar(data, i);

		if((i % 4) == 0 && i != 0)
		{
			SetPlrExtraData(plr, Format("%s%d", name, i/4 - 1), part);
			part = 0;
		}

		part |= (c << ((i % 4) * 8));
	}

	if(part != 0)
	{
		SetPlrExtraData(plr, Format("%s%d", name, i/4), part);
	}

	i = i/4 + 1;
	while(GetPlrExtraData(plr, Format("%s%d", name, i)))
	{
		SetPlrExtraData(plr, Format("%s%d", name, i++), 0);
	}
}

global func GetPlrExtraDataString(int plr, string name)
{
	var ret = "";
	var part = true;
	for(var i = 0; part != 0; ++i)
	{
		part = CastInt(GetPlrExtraData(plr, Format("%s%d", name, i)));
		for(var j = 0; j < 4; ++j)
		{
			var c = (part >> (j * 8)) & 0xFF;
			if(c == 0)
			{
				part = 0;
				break;
			}
			else
			{
				ret = Format("%s%c", ret, c);
			}
		}
	}
	return ret;
}

global func SetPlrExtraDataArray(int plr, string name, array arr)
{
	return SetPlrExtraDataString(plr, name, Serialize(arr));
}

global func GetPlrExtraDataArray(int plr, string name)
{
	var function = GetPlrExtraDataString(plr, name);
	if(function != "")
	{
		return eval(function);
	}
}

global func SetPlrExtraDataIntArray(int plr, string name, array arr)
{
	var lengthName = Format("%sL", name);

	var oldLength = CastInt(GetPlrExtraData(plr, lengthName));

	var length = GetLength(arr);

	for(var i = 0; i < length; ++i)
	{
		var partName = Format("%s%d", name, i);
		if(arr[i] != 0)
		{
			SetPlrExtraData(plr, partName, arr[i]);
		}
		else if(GetPlrExtraData(plr, partName) != 0)
		{
			SetPlrExtraData(plr, partName, 0);
		}
	}

	SetPlrExtraData(plr, lengthName, length);

	for(var i = length; i < oldLength; ++i)
	{
		var partName = Format("%s%d", name, i);
		if(GetPlrExtraData(plr, partName) != 0)
		{
			SetPlrExtraData(plr, partName, 0);
		}
	}
}

global func GetPlrExtraDataIntArray(int plr, string name)
{
	var length = CastInt(GetPlrExtraData(plr, Format("%sL", name)));

	var ret = CreateArray(length);

	for(var i = 0; i < length; ++i)
	{
		ret[i] = CastInt(GetPlrExtraData(plr, Format("%s%d", name, i)));
	}

	return ret;
}

global func EnableScripting()
{
	AddMsgBoardCmd("s", "ScriptingFunc(\"%s\", %player%)", C4MSGCMDR_Escaped);
}

global func ScriptingFunc(string script, int player)
{
	Log("-> %s", script);
	Log("= %v (by %s)", eval(script), GetTaggedPlayerName(player));
}

global func ParseInt(string int, bool hex)
{
	if(GetLength(int) == 0)
	{
		return "";
	}
	var ret = 0, neg = false;
	for(var i = 0; i < GetLength(int); ++i)
	{
		var c = GetChar(int, i);
		if(i == 0)
		{
			if(c == 45) // "-"
			{
				neg = true;
				continue;
			}
			else if(c == 43) // "+"
			{
				continue;
			}
		}
		c -= 48; // "0" == 48
		if(c < 0 || ((!hex && c > 9) || (hex && c > 54))) // "f" - "0" == 54
		{
			return "";
		}
		if(hex)
		{
			ret = ret << 4;
		}
		else
		{
			ret *= 10;
		}
		if(c > 9)
		{
			c -= 39;
		}
		ret += c;
	}
	return ret * (1 - (2 * neg));
}

global func ParseFloat(string float, int precision) // precision = number of digits after decimal point and multiplier of 10^precision
{
	precision = precision || 3;
	if(GetLength(float) == 0)
	{
		return "";
	}
	var ret = 0, neg = false, decimalPoint = -1;
	for(var i = 0; i < GetLength(float); ++i)
	{
		if(decimalPoint != -1 && decimalPoint + precision < i)
		{
			// out of precision
			break;
		}

		var c = GetChar(float, i);
		if(i == 0)
		{
			if(c == 45) // "-"
			{
				neg = true;
				continue;
			}
			else if(c == 43) // "+"
			{
				continue;
			}
		}
		c -= 48; // "0" == 48
		if(c < 0 || c > 9)
		{
			if((c == -2 || c == -4) && decimalPoint == -1) // "." || ","
			{
				decimalPoint = i;
				continue;
			}
			else
			{
				return "";
			}
		}
		ret *= 10;
		ret += c;
	}
	if(decimalPoint == -1)
	{
		decimalPoint = i - 1;
	}

	for(; i <= decimalPoint + precision; ++i)
	{
		ret *= 10;
	}

	return ret * (1 - (2 * neg));
}

global func CreateFilledArray()
{
	var ret = [];
	for(var i = 9; i >= 0; --i)
	{
		if(Par(i))
		{
			ret[i] = Par(i);
		}
	}
	return ret;
}

global func Find_Procedure(string proc)
{
	return [C4FO_Func, "Find_ProcedureCheck", proc];
}

global func Find_ProcedureCheck(string proc)
{
	return proc == GetProcedure();
}

global func GetSolidMask(object obj)
{
	obj = obj || this;
	return
	[
		GetObjectVal("SolidMask", 0, obj, 0), GetObjectVal("SolidMask", 0, obj, 1),
		GetObjectVal("SolidMask", 0, obj, 2), GetObjectVal("SolidMask", 0, obj, 3),
		GetObjectVal("SolidMask", 0, obj, 4), GetObjectVal("SolidMask", 0, obj, 5)
	];
}

//	getValue:
//		0 - offset index (the preferred way is to always get the offset index first and to pass the result to following calls for performance reasons)
//		1 - overlay ID
//		2 - overlay mode
//		3 - graphics definition ID
//		4 - graphics name
//		5 - action name
//		6 - blit mode
//		7 - index of Transformation-matrix
//		8 - enumerated overlay object (i.e. object number of the overlay object); WARNING: this is only valid and true directly after saving or loading a savegame

global func GetOverlayValueByIndex(int index, int startIndex, int getValue, object obj) // startIndex can be given as a valid index (retrieved with this function beforehand) and the asked index is used as offset (better performance for iterating over all indices)
{
	if(getValue < 0 || getValue > 8)
	{
		// invalid getValues could cause infinite loops
		return -2;
	}
	obj = obj || this;
	var found = false;
	if(index == 0)
	{
		if(getValue == 0)
		{
			if(GetObjectVal("GfxOverlay", 0, obj, startIndex) == 0)
			{
				// there is no such overlay
				return -1;
			}
			else
			{
				return startIndex;
			}
		}
		else if(getValue == 1)
		{
			return GetObjectVal("GfxOverlay", 0, obj, startIndex);
		}
		found = true;
	}
	for(var i = startIndex + 1, foundIndex = 0; ;) // skip overlay ID
	{
		var val = GetObjectVal("GfxOverlay", 0, obj, i);
		if(val == 0)
		{
			// there is no overlay left
			return -1;
		}
		if(val == GFXOV_MODE_Object)
		{
			// this is the overlay mode GFXOV_MODE_Object. Graphics-Definition and -Name are left out
			if(found && (getValue == 3 || getValue == 4))
			{
				return 0;
			}
			else if(found && getValue == 2)
			{
				return GFXOV_MODE_Object;
			}
		}
		else if(GetType(val) == C4V_C4ID)
		{
			if(found)
			{
				if(getValue == 3)
				{
					return val;
				}
				else if(getValue == 4)
				{
					return GetObjectVal("GfxOverlay", 0, obj, i + 1);
				}
			}
			i += 2; // skip Graphics-Definition and -Name, so i points to OverlayMode here too
			if(found && getValue == 2)
			{
				return GetObjectVal("GfxOverlay", 0, obj, i);
			}
		}
		else
		{
			//something went wrong already
			return -3;
		}

		if(found)
		{
			if(getValue == 5)
			{
				return GetObjectVal("GfxOverlay", 0, obj, i + 1);
			}
			else if(getValue == 6)
			{
				return GetObjectVal("GfxOverlay", 0, obj, i + 2);
			}
			else if(getValue == 7)
			{
				return i + 4;
			}
		}

		i += 10; // this is either the last row of the Transformation matrix or the Color-Modulation
		val = GetObjectVal("GfxOverlay", 0, obj, i);

		if(GetType(val) == C4V_String)
		{
			// part of the matrix, skip it
			i += 3;
		}

		if(found && getValue == 8)
		{
			return GetObjectVal("GfxOverlay", 0, obj, i + 2);
		}

		i += 3; // and the rest

		if(++foundIndex == index)
		{
			if(GetObjectVal("GfxOverlay", 0, obj, i) == 0)
			{
				// there is no overlay left
				return -1;
			}
			else
			{
				found = true;
				if(getValue == 0)
				{
					return i;
				}
				else if(getValue == 1)
				{
					return GetObjectVal("GfxOverlay", 0, obj, i);
				}
			}
		}

		++i; // skip the next overlay ID
	}
}

global func GetOverlayValueOffsetByID(int overlay, object obj)
{
	obj = obj || this;

	if(overlay != 0)
	{
		var offset = 0, diffIndex = 0;
		while((offset = obj->GetOverlayValueByIndex(diffIndex, offset)) >= 0)
		{
			if(GetOverlayValueByIndex(0, offset, 1) == overlay)
			{
				return offset;
			}
			diffIndex = 1;
		}
	}

	return -1;
}

global func GetObjDrawTransform(int overlay, int overlayOffset, object obj)
{
	obj = obj || this;
	if(overlay == 0)
	{
		var first = GetObjectVal("DrawTransform", 0, obj, 0);
		if(first == 0)
		{
			return [1000, 0, 0, 0, 1000, 0];
		}
		var ret = [ParseFloat(first, 3), ParseFloat(GetObjectVal("DrawTransform", 0, obj, 1), 3), ParseFloat(GetObjectVal("DrawTransform", 0, obj, 2), 3), ParseFloat(GetObjectVal("DrawTransform", 0, obj, 3), 3), ParseFloat(GetObjectVal("DrawTransform", 0, obj, 4), 3), ParseFloat(GetObjectVal("DrawTransform", 0, obj, 5), 3)];

		var rest = GetObjectVal("DrawTransform", 0, obj, 7); // 6 is left out intentionally, because its only FlipDir (used internally for Actions with FlipDir)
		if(GetType(rest) == C4V_String) // the last 3 matrix-values are only decompiled if they are not the default of [0, 0, 1.0]
		{
			SetLength(ret, 9);
			ret[6] = ParseFloat(rest, 3);
			ret[7] = ParseFloat(GetObjectVal("DrawTransform", 0, obj, 8), 3);
			ret[8] = ParseFloat(GetObjectVal("DrawTransform", 0, obj, 9), 3);
		}

		return ret;
	}
	else
	{
		var index = 0;
		if(overlay == -1)
		{
			index = overlayOffset;
		}
		else
		{
			index = obj->GetOverlayValueOffsetByID(overlay);
		}
		if(index < 0)
		{
			return index;
		}
		index = obj->GetOverlayValueByIndex(0, index, 7);
		if(index < 0)
		{
			return index;
		}

		var ret = [ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index), 3), ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index + 1), 3), ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index + 2), 3), ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index + 3), 3), ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index + 4), 3), ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index + 5), 3)];

		var rest = GetObjectVal("GfxOverlay", 0, obj, index + 7); // 6 is left out intentionally, because its only FlipDir (used internally for Actions with FlipDir)
		if(GetType(rest) == C4V_String) // the last 3 matrix-values are only decompiled if they are not the default of [0, 0, 1.0]
		{
			SetLength(ret, 9);
			ret[6] = ParseFloat(rest, 3);
			ret[7] = ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index + 8), 3);
			ret[8] = ParseFloat(GetObjectVal("GfxOverlay", 0, obj, index + 9), 3);
		}

		return ret;
	}
}

global func GetShape(object obj)
{
	obj = obj || this;
	return [GetObjectVal("Offset", 0, obj, 0), GetObjectVal("Offset", 0, obj, 1), GetObjectVal("Width", 0, obj), GetObjectVal("Height", 0, obj)];
}

global func InRect(array point, array rect)
{
	var x = point[0], y = point[1];
	return rect[0] < x && x < rect[0] + rect[2] && rect[1] < y && y < rect[1] + rect[3];
}

global func GetPlayerByID(int id)
{
	for(var i = 0; i < GetPlayerCount(); ++i)
	{
		var plr = GetPlayerByIndex(i);
		if(GetPlayerID(plr) == id)
		{
			return plr;
		}
	}

	return NO_OWNER;
}
