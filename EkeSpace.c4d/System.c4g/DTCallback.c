/*-- Extensible callback system --*/
#strict 2

static const CallbackTarget_Bind = -1;
static const CallbackTarget_Global = -2;
static const CallbackTarget_Scenario = -3;

// NOTE: fast callbacks (fast = true for ObjectCallback or DefinitionCallback) use ObjectCall/DefinitionCall directly for greater performance if possible (refs == 0 and GetLength(args) <= 8 for CallA()) and thus must be real functions of the desired object/definition. safe mode is ignored for fast callbacks

global func GlobalCallback(string name) { return [CallbackTarget_Global, name]; }
global func ScenarioCallback(string name) { return [CallbackTarget_Scenario, name]; }
global func ObjectCallback(string name, bool fast, object target) { return [target || this || FatalError("ObjectCallback without target object"), name, fast]; }
global func DefinitionCallback(string name, bool fast, id target) { return [target || GetID() || FatalError("DefinitionCallback without target definition"), name, fast]; }
global func Callback(string name, target) { return [target || this || GetID() || CallbackTarget_Global, name]; }
global func BindCallback(callback, array binding) { return [CallbackTarget_Bind, callback, binding]; }

static const BindCallback_Bind_Value = -1;
static const BindCallback_Bind_Context = -2;
static const BindCallback_Bind_ContextDef = -3;
static const BindCallback_Bind_CallbackResult = -4;
static const BindCallback_Bind_ArgumentArrayPart = -5;
static const BindCallback_Bind_Reference = -6;
global func Bind(value) { return [BindCallback_Bind_Value, value]; }
global func Bind_Context() { return [BindCallback_Bind_Context]; }
global func Bind_ContextDef() { return [BindCallback_Bind_ContextDef]; }
global func Bind_CallbackResult(callback) { return [BindCallback_Bind_CallbackResult, callback]; }
global func Bind_ArgumentArrayPart(int argument, part)
{
	if(GetType(part) != C4V_Array)
	{
		part = [part];
	}
	return [BindCallback_Bind_ArgumentArrayPart, argument, part];
}
global func Bind_Reference(array scopedVar) { return [BindCallback_Bind_Reference, scopedVar]; }

global func Call(callback)
{
	if(GetType(callback) == C4V_String)
	{
		return _inherited(callback, ...);
	}
	else
	{
		return CallA(callback, CreateFilledArray(...));
	}
}

global func CallA(callback, args, bool safe, array refs)
{
	if(GetType(callback) == C4V_String)
	{
		callback = [this, callback, true];
	}

	if(GetType(callback) != C4V_Array)
	{
		return _inherited(callback, args, ...);
	}

	var target = callback[0], function = callback[1];

	if((GetType(target) == C4V_C4Object || GetType(target) == C4V_C4ID) && GetLength(callback) == 3 && callback[2] && (!refs || refs == []) && GetLength(args) <= 8) // fast callback
	{
		if(GetType(target) == C4V_C4Object)
		{
			return ObjectCall(target, function, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
		}
		else if(GetType(target) == C4V_C4ID)
		{
			return DefinitionCall(target, function, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
		}
	}

	refs = refs || [];

	if(target == CallbackTarget_Scenario)
	{
		return GameCall(function, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
	}
	else if(target == CallbackTarget_Bind)
	{
		return CallA(function, BindArgs(callback[2], args, safe, refs), safe, refs);
	}

	if(GetType(target) == C4V_C4Object || GetType(target) == C4V_C4ID || target == CallbackTarget_Global)
	{
		var safeModifier = "";
		if(safe)
		{
			safeModifier = "~";
		}
		var argsStr = "", pos = 0;
		for(var arg in args)
		{
			if(pos > 0)
			{
				argsStr = Format("%s, ", argsStr);
			}
			if(refs[pos])
			{
				argsStr = Format("%sScopedVar(%s)", argsStr, Serialize(arg));
			}
			else
			{
				argsStr = Format("%s%s", argsStr, Serialize(arg));
			}
			++pos;
		}

		if(target == CallbackTarget_Global)
		{
			return GlobalEval(Format("%s(%s)", function, argsStr));
		}
		else if(GetType(target) == C4V_C4Object || GetType(target) == C4V_C4ID)
		{
			return eval(Format("%s->%s%s(%s)", Serialize(target), safeModifier, function, argsStr));
		}
	}
	else
	{
		if(this)
		{
			return this->~CallCustom(callback, args, ...);
		}
		else if(GetID())
		{
			return GetID()->~CallCustom(callback, args, ...);
		}
		else
		{
			return CallCustom(callback, args, ...);
		}
	}
}

global func CallCustom() { return _inherited(...); }

global func BindArgs_ArgumentArrayPart(array binding, array args, bool safe)
{
	var ret = args[binding[0]];
	for(var i = 1; i < GetLength(binding); ++i)
	{
		if(!safe || GetType(ret) == C4V_Array)
		{
			ret = ret[binding[i]];
		}
		else
		{
			return 0;
		}
	}
	return ret;
}

global func BindCustomArgs() { return _inherited(...); } // this allows "overloading" this function even if the "overloading" function is loaded before

global func BindArgs(array binding, array args, bool safe, array& refs)
{
	refs = [];
	var ret = CreateArray(GetLength(binding)), pos = 0;
	for(var bind in binding)
	{
		if(GetType(bind) == C4V_Int || GetType(bind) == C4V_Any && bind >= 0)
		{
			ret[pos] = args[bind];
		}
		else if(GetType(bind) == C4V_Array && GetLength(bind))
		{
			if(bind[0] == BindCallback_Bind_Value)
			{
				ret[pos] = bind[1];
			}
			else if(bind[0] == BindCallback_Bind_Context)
			{
				ret[pos] = this;
			}
			else if(bind[0] == BindCallback_Bind_ContextDef)
			{
				ret[pos] = GetID();
			}
			else if(bind[0] == BindCallback_Bind_CallbackResult)
			{
				ret[pos] = CallA(bind[1], args, safe);
			}
			else if(bind[0] == BindCallback_Bind_ArgumentArrayPart)
			{
				ret[pos] = BindArgs_ArgumentArrayPart(bind[2], args[bind[1]], safe);
			}
			else if(bind[0] == BindCallback_Bind_Reference)
			{
				refs[pos] = true;
				ret[pos] = bind[1];
			}
			else if(GetType(bind[0]) == C4V_Int && bind[0] < 0)
			{
				if(this)
				{
					ret[pos] = this->~BindCustomArgs(bind, args, safe);
				}
				else if(GetID())
				{
					ret[pos] = GetID()->~BindCustomArgs(bind, args, safe);
				}
				else
				{
					ret[pos] = BindCustomArgs(bind, args, safe);
				}
			}
			else
			{
				ret[pos] = BindArgs(bind, args, safe);
			}
		}
		else
		{
			FatalError(Format("BindArgs: incorrect binding %v", bind));
		}
		++pos;
	}
	return ret;
}

global func GlobalEval(string code)
{
	var effect = AddEffect("IntGlobalEval", 0, 1);
	var ret = EffectCall(0, effect, "Eval", code);
	RemoveEffect(0, 0, effect);
	return ret;
}

global func FxIntGlobalEvalEval(object target, int effectNumber, string code)
{
	return eval(code);
}

global func foreach(array arr, callback)
{
	var i = 0;
	for(var val in arr)
	{
		CallA(callback, [val, i++]);
	}
}

global func CheckCallback(callback)
{
	if(GetType(callback) == C4V_String)
	{
		return true;
	}

	if(GetType(callback) == C4V_Array)
	{
		if(GetType(callback[0]) == C4V_Int)
		{
			if(callback[0] == CallbackTarget_Bind && GetLength(callback) == 3)
			{
				if(CheckCallback(callback[1]) && CheckBindCallbackBinding(callback[2]))
				{
					return true;
				}
			}
			else if(callback[0] == CallbackTarget_Global || callback[0] == CallbackTarget_Scenario)
			{
				if(GetLength(callback) == 2 && GetType(callback[1]) == C4V_String && callback[1] != "")
				{
					return true;
				}
			}
		}
		else if(GetType(callback[0]) == C4V_C4ID || GetType(callback[0]) == C4V_C4Object)
		{
			if(GetLength(callback) == 2 || (GetLength(callback) == 3 && (!callback[2] || GetType(callback[2]) == C4V_Bool))) // length 2 for callbacks created by Callback() or Object/DefinitionCallback() before fast was introduced
			{
				if(GetType(callback[1]) == C4V_String && callback[1] != "")
				{
					return true;
				}
			}
		}
	}

	if(this)
	{
		return this->~CheckCustomCallback(callback, ...);
	}
	else if(GetID())
	{
		return GetID()->~CheckCustomCallback(callback, ...);
	}
	else
	{
		return CheckCustomCallback(callback, ...);
	}
}

// to silence the error if no ScopedVars are included
global func CheckScopedVar() { return _inherited(...); }

global func CheckCustomCallback() { return _inherited(...); }

global func CheckBindCallbackBinding(array binding)
{
	for(var b in binding)
	{
		if(b && GetType(b) != C4V_Int)
		{
			if(GetType(b) == C4V_Array)
			{
				if(b[0] == BindCallback_Bind_Value)
				{
					if(GetLength(b) != 2)
					{
						return false;
					}
				}
				else if(b[0] == BindCallback_Bind_Context || b[0] == BindCallback_Bind_ContextDef)
				{
					continue;
				}
				else if(b[0] == BindCallback_Bind_CallbackResult)
				{
					if(GetLength(b) != 2 || !CheckCallback(b[1]))
					{
						return false;
					}
				}
				else if(b[0] == BindCallback_Bind_ArgumentArrayPart)
				{
					if(GetLength(b) != 3)
					{
						return false;
					}

					if(b[1] && (GetType(b[1]) != C4V_Int || b[1] < 0))
					{
						return false;
					}

					for(var part in b[2])
					{
						if(part && (GetType(part) != C4V_Int || part < 0))
						{
							return false;
						}
					}
				}
				else if(b[0] == BindCallback_Bind_Reference)
				{
					if(GetLength(b) != 2 || !CheckScopedVar(b[1]))
					{
						return false;
					}
				}
				else if(GetType(b[0]) == C4V_Int && b[0] < 0)
				{
					var ret;
					if(this)
					{
						ret = this->~CheckBindCallbackCustomBinding(b);
					}
					else if(GetID())
					{
						ret = GetID()->~CheckBindCallbackCustomBinding(b);
					}
					else
					{
						ret = CheckBindCallbackCustomBinding(b);
					}
					if(!ret)
					{
						return false;
					}
				}
				else
				{
					if(!CheckBindCallbackBinding(b))
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
		else if(b < 0)
		{
			return false;
		}
	}
	return true;
}

global func CheckBindCallbackCustomBinding() { return _inherited(...); }