#include "StdAfx.h"
#include "XMLHelper.h"

CXMLHelper::CXMLHelper(void)
{
}

CXMLHelper::~CXMLHelper(void)
{
}

BOOL CXMLHelper::ExtractSubDoc(int & iStartPos, const char * szXMLDoc, const char * szXMLSubDocTagName, CString & csXMLSubDoc)
{
	csXMLSubDoc = _T("");
	CString csXMLDoc = szXMLDoc;

	// ok if our tag is a normal tag <sub><sub/> then we'll just grab it out
	// if we find this </sub then we just go until we get the next >
	// so first get the normal scenario
	CString csStartTag1 = _T("");
	CString csEndTag1 = _T("");
	CString csSingleDoc = _T("");
	CString csSingledDocEndTag = _T("");
	csStartTag1.Format("<%s>", szXMLSubDocTagName);
	csEndTag1.Format("</%s>", szXMLSubDocTagName);
	csSingleDoc.Format("<%s ", szXMLSubDocTagName);
	csSingledDocEndTag.Format("/>");


	int iEndPos = 0;
	int iCount = 0;
	int iStart = csXMLDoc.Find(csStartTag1, iStartPos);

	// if it fails the first time try searching for the end tag
	// if we can't find the end tag - THEN it's a single doc, if we can then we need to form the beginning tag 
	// like this <%s because there might be attributes included
	if (iStart == -1)
	{
		iEndPos = csXMLDoc.Find(csEndTag1, iStartPos);
		if (iEndPos != -1)
		{
			csStartTag1.Format("<%s ", szXMLSubDocTagName);
			iStart = csXMLDoc.Find(csStartTag1, iStartPos); // if we still can't find it after this THEN search for a single type doc as a last resort
		}
	}

	if (iStart != -1)
	{
		// ok we found our start tag find the end tag
		iEndPos = csXMLDoc.Find(csEndTag1, iStart+csStartTag1.GetLength());

		if (iEndPos != -1)
		{
			// ok now extract our sub doc
			// first calculate the total length of our start tag all the way through and including the end tag
			iCount = (iEndPos + csEndTag1.GetLength()) - iStart;
			csXMLSubDoc = csXMLDoc.Mid(iStart, iCount);
			// now set the start for the next tag so we can iterate through
			iStartPos = iEndPos + csEndTag1.GetLength();
			return TRUE;
		}
		else
		{
			return FALSE; // missing the end tag
		}
	}
	else
	{
		iStart = csXMLDoc.Find(csSingleDoc, iStartPos);

		if (iStart == -1)
		{
			return FALSE;
		}
		iCount = 0;
		// ok we have the start of the string, now let's count through to the > char
		iEndPos = csXMLDoc.Find("/>", iStart+csSingleDoc.GetLength());

		if (iEndPos != -1)
		{
			// ok now extract our sub doc
			// first calculate the total length of our start tag all the way through and including the end tag
			iCount = (iEndPos + csSingledDocEndTag.GetLength()) - iStart;
			csXMLSubDoc = csXMLDoc.Mid(iStart, iCount);
			// now set the start for the next tag so we can iterate through
			iStartPos = iEndPos + csSingledDocEndTag.GetLength();
			return TRUE;
		}
		else
		{
			return FALSE; // missing the end tag
		}
	}

	return FALSE;
}
