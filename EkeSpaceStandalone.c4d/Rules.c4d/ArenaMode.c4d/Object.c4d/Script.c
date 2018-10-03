#strict 2

static arenaModeRule;

func Initialize()
{
    arenaModeRule = this;
}

protected func Activate(iByPlayer)
{
  MessageWindow(GetDesc(), iByPlayer);
  return(1);
}