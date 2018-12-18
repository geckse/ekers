#strict 2

// Variation of PathFree / ForLine from Standard.cpp

global func PathBlockedPosition(int xStart, int yStart, int xEnd, int yEnd, int& xBlocked, int& yBlocked)
{
	if(this)
	{
		return ROCK->PathBlockedPosition(xStart, yStart, xEnd, yEnd, xBlocked, yBlocked);
	}

	var d, aincr, bincr;
	var dx = Abs(xEnd - xStart);
	var dy = Abs(yEnd - yStart);

	xBlocked = xStart;
	yBlocked = yStart;
	if(GBackSolid(xBlocked, yBlocked))
	{
		return true;
	}

	if(Abs(xEnd - xStart) < Abs(yEnd - yStart))
	{
		var xincr = 2 * (xEnd > xStart) - 1;

		d = 2 * dx - dy;

		aincr = 2 * (dx - dy);
		bincr = 2 * dx;

		if(yEnd >= yStart)
		{
			for(yBlocked = yStart + 1; yBlocked <= yEnd; ++yBlocked)
			{
				if(d >= 0)
				{
					xBlocked += xincr;
					d += aincr;
				}
				else
				{
					d += bincr;
				}

				if(GBackSolid(xBlocked, yBlocked))
				{
					return true;
				}
			}
		}
		else
		{
			for(yBlocked = yStart - 1; yBlocked >= yEnd; --yBlocked)
			{
				if(d >= 0)
				{
					xBlocked += xincr;
					d += aincr;
				}
				else
				{
					d += bincr;
				}

				if(GBackSolid(xBlocked, yBlocked))
				{
					return true;
				}
			}
		}
	}
	else
	{
		var yincr = 2 * (yEnd > yStart) - 1;

		d = 2 * dy - dx;

		aincr = 2 * (dy - dx);
		bincr = 2 * dy;

		if(xEnd >= xStart)
		{
			for(xBlocked = xStart + 1; xBlocked <= xEnd; ++xBlocked)
			{
				if(d >= 0)
				{
					yBlocked += yincr;
					d += aincr;
				}
				else
				{
					d += bincr;
				}

				if(GBackSolid(xBlocked, yBlocked))
				{
					return true;
				}
			}
		}
		else
		{
			if(GBackSolid(xBlocked, yBlocked))
			{
				return true;
			}
			for(xBlocked = xStart - 1; xBlocked >= xEnd; --xBlocked)
			{
				if(d >= 0)
				{
					yBlocked += yincr;
					d += aincr;
				}
				else
				{
					d += bincr;
				}

				if(GBackSolid(xBlocked, yBlocked))
				{
					return true;
				}
			}
		}
	}

	return false;
}