#strict 2

static const DT_Menu_SymbolDummy = MS7I;

func SetSymbol(id symbol, int nr)
{
	SetGraphics(0, this, symbol);
	SetPicture(GetDefCoreVal("Picture", "DefCore", symbol, 0) + nr * GetDefCoreVal("Picture", "DefCore", symbol, 2), GetDefCoreVal("Picture", "DefCore", symbol, 1), GetDefCoreVal("Picture", "DefCore", symbol, 2), GetDefCoreVal("Picture", "DefCore", symbol, 3));
	return this;
}

func SetColor(int color)
{
	SetClrModulation(color);
	return this;
}
