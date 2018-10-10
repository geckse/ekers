#strict 2

global func ArrayErase(array& arr, int index)
{
	if(index < GetLength(arr))
	{
		for(var i = index; i < GetLength(arr) - 1; ++i)
		{
			arr[i] = arr[i + 1];
		}
		SetLength(arr, GetLength(arr) - 1);
	}
}

global func ArrayEraseItem(array& arr, item, bool multiple)
{
	var index, count = 0;
	while((index = GetIndexOf2(item, arr)) != -1)
	{
		ArrayErase(arr, index);
		if(!multiple)
		{
			return index;
		}
		++count;
	}
	return (!multiple && -1) || count;
}

global func ArrayInsert(array& arr, int index, value)
{
	for(var i = GetLength(arr); i > index; --i)
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = value;
}

global func ArrayAppend(array& arr, value)
{
	arr[GetLength(arr)] = value;
}

global func ArrayAppendArray(array& arr, array append)
{
	var i = GetLength(arr);
	SetLength(arr, GetLength(arr) + GetLength(append));
	for(var val in append)
	{
		arr[i++] = val;
	}
}
