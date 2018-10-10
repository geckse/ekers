#strict 2
// TODO: ScopedVars with temporary target (like a reference to a function local var)

static const ScopedVar_Global = 1;
static const ScopedVar_Local = 2;
static const ScopedVar_ArrayIndex = 3;

global func GlobalVar(name) { return [ScopedVar_Global, name]; }
global func LocalVar(name, object target) { return [ScopedVar_Local, name, target || this]; }
global func ArrayVar(index, array scopedVar) { return [ScopedVar_ArrayIndex, scopedVar, index]; }

global func &ScopedVar(array variable)
{
	if(!variable)
	{
		return 0;
	}
	if(variable[0] == ScopedVar_Global)
	{
		if(GetType(variable[1]) == C4V_String)
		{
			return GlobalN(variable[1]);
		}
		else
		{
			return Global(variable[1]);
		}
	}
	else if(variable[0] == ScopedVar_Local)
	{
		if(GetType(variable[1]) == C4V_String)
		{
			return LocalN(variable[1], variable[2]);
		}
		else
		{
			return Local(variable[1], variable[2]);
		}
	}
	else if(variable[0] == ScopedVar_ArrayIndex)
	{
		var index = variable[2];
		if(GetType(index) != C4V_Int && GetType(index) != C4V_Any)
		{
			index = ScopedVar(index);
		}
		return ScopedVar(variable[1])[index];
	}
	else
	{
		if(this)
		{
			return ScopedVar(this->~CustomScopedVar(variable));
		}
		else if(GetID())
		{
			return ScopedVar(GetID()->~CustomScopedVar(variable));
		}
		else
		{
			return ScopedVar(CustomScopedVar(variable));
		}
	}
}

global func CustomScopedVar() { return _inherited(...); } // this allows "overloading" this function even if the "overloading" function is loaded before

global func CheckScopedVar(array variable)
{
	if(!variable)
	{
		return false;
	}

	if(GetType(variable[0]) == C4V_Int)
	{
		if(variable[0] == ScopedVar_Global || variable[0] == ScopedVar_Local)
		{
			if(!variable[1] || GetType(variable[1]) == C4V_Int || (GetType(variable[1]) == C4V_String && variable[1] != ""))
			{
				return true;
			}
		}

		if(variable[0] == ScopedVar_ArrayIndex)
		{
			if(CheckScopedVar(variable[1]) && !variable[2] || (GetType(variable[2]) == C4V_Int && variable[2] >= 0))
			{
				return true;
			}
		}
	}

	if(this)
	{
		return this->~CheckCustomScopedVar(variable);
	}
	else if(GetID())
	{
		return GetID()->~CheckCustomScopedVar(variable);
	}
	else
	{
		return CheckCustomScopedVar(variable);
	}
}

global func CheckCustomScopedVar() { return _inherited(...); }