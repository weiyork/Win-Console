#ifndef _BASCI_CASE1_
#define _BASCI_CASE1_

class CCase1
{
public:
	static double GetAvenue(double invest, int nYear, double rate)
	{
		if(nYear==1)
			return invest*(1+rate);
		else
		{
			return (GetAvenue(invest, nYear-1, rate)*(1+rate) + invest*(1+rate));
		}
	}
};






#endif