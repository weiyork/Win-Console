#pragma once

class CXMLHelper
{
public:
	CXMLHelper(void);
	~CXMLHelper(void);
	BOOL ExtractSubDoc(int & iStartPos, const char * szXMLDoc, const char * szXMLSubDocTagName, CString & csXMLSubDoc);

	CString StrInt(int iNumber)
	{
		CString csNumber = _T("");
		csNumber.Format("%d", iNumber);
		return csNumber;
	}

	int IntStr(const char * szNumber)
	{
		CString csNumber = szNumber;
		if (!csNumber.GetLength())
		{
			return 0;
		}
		// check to make sure this is a number
		for (int i = 0; i < csNumber.GetLength(); i++)
		{
			if (csNumber[i] != '0' &&
				csNumber[i] != '1' &&
				csNumber[i] != '2' &&
				csNumber[i] != '3' &&
				csNumber[i] != '4' &&
				csNumber[i] != '5' &&
				csNumber[i] != '6' &&
				csNumber[i] != '7' &&
				csNumber[i] != '8' &&
				csNumber[i] != '9')
			{
				return 0;
			}
		}
		return atoi(szNumber);
	}
};
