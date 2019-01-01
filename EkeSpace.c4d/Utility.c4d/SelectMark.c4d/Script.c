#strict 2

local attachEffect;

global func CreateSelectMark() { return CreateObject(SELM, 0, 0, GetOwner()); }

func Padding(int forVal) { return (forVal < 3) * 2; }

func Initialize()
{
	Hide();
	SetAction("UpperLeft");
	Primary();
}

func MarkObject(object obj, int time, bool noShow)
{
	if(!noShow)
	{
		Show();
	}
	var id = GetID(obj);
	var w = GetObjWidth(obj);
	var h = GetObjHeight(obj);
	var x = GetX(obj) + GetDefOffset(id) + (GetDefWidth(id) - w) / 2;
	var y = GetY(obj) + GetDefOffset(id, 1) + (GetDefHeight(id) - h) / 2;
	var xOff = 0;
	var xPad = Padding(w);
	var yPad = Padding(h);
	if(x - xPad < 0)
	{
		x -= (xOff = -(w + 2 * xPad));
	}
	SetPosition(x - xPad, y - yPad);
	SetObjDrawTransform(1000, 0, xOff * 1000, 0, 1000, 0, this, 0);
	SetObjDrawTransform(1000, 0, (xOff + w + 2 * xPad) * 1000, 0, 1000, 0, this, 1);
	SetObjDrawTransform(1000, 0, xOff * 1000, 0, 1000, (h + 2 * yPad) * 1000, this, 2);
	SetObjDrawTransform(1000, 0, (xOff + w + 2 * xPad) * 1000, 0, 1000, (h + 2 * yPad) * 1000, this, 3);

	if(time != -1)
	{
		if(attachEffect && attachEffect[0] != obj)
		{
			RemoveEffect(0, attachEffect[0], attachEffect[1]);
		}
		if(!attachEffect)
		{
			AddEffect("SelectionMarkAttach", obj, 1, 1, this, 0, time);
		}
	}
	return this;
}

func Hide()
{
	SetVisibility(VIS_None, this);
}

func Show()
{
	SetVisibility(VIS_Owner, this);
}

func FxSelectionMarkAttachStart(object target, int effectNumber, int temp, int time)
{
	attachEffect = [target, effectNumber];
	EffectVar(0, target, effectNumber) = time;
}

func FxSelectionMarkAttachTimer(object target, int effectNumber, int effectTime)
{
	var time = EffectVar(0, target, effectNumber);
	if(time && effectTime > time)
	{
		return RemoveObject();
	}
	MarkObject(target, -1, true);
}

func FxSelectionMarkAttachStop(object target, int effectNumber)
{
	attachEffect = 0;
}

func Primary()
{
	SetGraphics();
	SetGraphics(0, this, GetID(), 1, GFXOV_MODE_Action, "UpperRight");
	SetGraphics(0, this, GetID(), 2, GFXOV_MODE_Action, "LowerLeft");
	SetGraphics(0, this, GetID(), 3, GFXOV_MODE_Action, "LowerRight");
	return this;
}

func Secondary()
{
	SetGraphics("2");
	SetGraphics("2", this, GetID(), 1, GFXOV_MODE_Action, "UpperRight");
	SetGraphics("2", this, GetID(), 2, GFXOV_MODE_Action, "LowerLeft");
	SetGraphics("2", this, GetID(), 3, GFXOV_MODE_Action, "LowerRight");
	return this;
}
