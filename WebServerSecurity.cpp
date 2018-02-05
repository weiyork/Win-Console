#include "stdafx.h"
//#include "WebServerSecurity.h"

CVIQWebServerSecurity::CVIQWebServerSecurity()
{
}

CVIQWebServerSecurity::~CVIQWebServerSecurity()
{
}

BOOL CVIQWebServerSecurity::ConvertDBString( BYTE *pByte, int nSize, CString &strReturn )
{
	BOOL bReturn = FALSE;
	if( pByte && (nSize > 0) )
	{
		CString csTest = "";
		csTest.Format("###NSC### CheckWebUserLogin ConvertDBString nSize %d",nSize);
		OutputDebugString(csTest);
		int nLength = (int)(pByte)[0];
		csTest.Format("###NSC### CheckWebUserLogin ConvertDBString nLength %d",nLength);
		OutputDebugString(csTest);
		if( nLength+1 == nSize )
		{
			for(int i=0;i<nSize;i++ )
			{
				strReturn += pByte[i];
			}
			csTest.Format("###NSC### CheckWebUserLogin ConvertDBString string '%s'",strReturn);
			OutputDebugString(csTest);
			bReturn = TRUE;
		}
	}
	return bReturn;
}

CString CVIQWebServerSecurity::EncryptAnnotation( const CString &strAnnotation )
{
	CString strReturn = "";
	strReturn = EncryptString( ANNOTATION_KEY, strAnnotation );
	return strReturn;
}

CString CVIQWebServerSecurity::DecryptAnnotation( const CString &strAnnotation )
{
	CString strReturn = "";
	strReturn = DecryptString( ANNOTATION_KEY, strAnnotation );
	return strReturn;

}

CString CVIQWebServerSecurity::EncryptCFUserID( const CString &strUserID )
{
	CString strReturn = "";
	strReturn = EncryptString( CFUSERID, strUserID );
	return strReturn;
}

CString CVIQWebServerSecurity::DecryptCFUserID( const CString &strUserID )
{
	CString strReturn = "";
	strReturn = DecryptString( CFUSERID, strUserID );
	return strReturn;
}

CString CVIQWebServerSecurity::EncryptCFPassword( const CString &strPassword )
{
	CString strReturn = "";
	strReturn = EncryptString( CFPASSWORD, strPassword );
	return strReturn;
}

CString CVIQWebServerSecurity::DecryptCFPassword( const CString &strPassword )
{
	CString strReturn = "";
	strReturn = DecryptString( CFPASSWORD, strPassword );
	return strReturn;
}

CString CVIQWebServerSecurity::EncryptWebUserPassword( const CString &strPassword )
{
	CString strReturn = "";
	strReturn = EncryptString( WEBUSERPASSWORD, strPassword );
	return strReturn;
}

CString CVIQWebServerSecurity::DecryptWebUserPassword( const CString &strPassword )
{
	CString strReturn = "";
	strReturn = DecryptString( WEBUSERPASSWORD, strPassword );
	return strReturn;
}

CString CVIQWebServerSecurity::EncryptCreditCardNumber( const CString &strCreditCard )
{
	CString strReturn = "";
	strReturn = EncryptString( CREDITCARDNUMBER, strCreditCard );
	return strReturn;
}

CString CVIQWebServerSecurity::DecryptCreditCardNumber( const CString &strCreditCard )
{
	CString strReturn = "";
	strReturn = DecryptString( CREDITCARDNUMBER, strCreditCard );
	return strReturn;
}

CString CVIQWebServerSecurity::EncryptExpiryDate( const CString &strExpiryDate )
{
	CString strReturn = "";
	strReturn = EncryptString( EXPIRYDATE, strExpiryDate );
	return strReturn;
}

CString CVIQWebServerSecurity::DecryptExpiryDate( const CString &strExpiryDate )
{
	CString strReturn = "";
	strReturn = DecryptString( EXPIRYDATE, strExpiryDate );
	return strReturn;
}

CString CVIQWebServerSecurity::EncryptString(const CString &strKey, const CString &strInput)
{
	//One block testing
	CString strReturn = "";
	try
	{
		//  // Input data
		unsigned char key[32];                       // The key
		unsigned char inText[255];
		memset( inText,0,255);
		memset(key,0,32);
		 int i;
		for(i=0; i<32 ; i++ )
		{
			key[i] = unsigned char(strKey[i]);
		}
		int nTextLen = strInput.GetLength();        // Plain text length
		if( nTextLen > 255 )
		{
			nTextLen = 255;
		}
		for( i=0;i<nTextLen;i++ )
		{
			inText[i] = unsigned char(strInput[i]);
		}
		//
		//  // Encrypting
		Rijndael rin;
		//int nOutputLen = strInput.GetLength() + 16;
		unsigned char output[255];
		memset(output,0,255);
		
		rin.init(Rijndael::CBC,Rijndael::Encrypt,key,Rijndael::Key32Bytes);
		//  // It is a good idea to check the error code
		int len = rin.padEncrypt(inText, nTextLen, output);
	    if(len >= 0)
		{
			//strReturn = len;
			for( int j=0; j<len; j++ )
			{
				strReturn += output[j];
			}
		}
	/*	unsigned char output2[255];
		memset(output2,0,255);
	
		Rijndael temp;
		temp.init(Rijndael::CBC,Rijndael::Decrypt, key, Rijndael::Key32Bytes);
		len = temp.padDecrypt(output, len, output2);
		if(len >= 0)
		{
			strReturn = output2;
		}*/

		//  else encryptError(len);
		//
	}
	catch(...)
	{
	//	cout << roException.what() << endl;
	}
	return strReturn;
}

CString CVIQWebServerSecurity::DecryptString(const CString &strKey, const CString &strInput)
{
	//One block testing
	CString strReturn = "";
	try
	{
		//  // Input data
		unsigned char key[32];                       // The key
		unsigned char inText[255];
		memset( inText,0,255);
		memset(key,0,32);
		int i;
		for( i=0; i<32 ; i++ )
		{
			key[i] = unsigned char(strKey[i]);
		}
		CString strInputTemp = strInput;
		int nTextLen = strInput.GetLength()-1;        // Plain text length
		if( nTextLen > 0 )
		{
			int nDecryptLen = (int)strInput[0];
			for( i=1;i<=nTextLen;i++ )
			{
				inText[i-1] = unsigned char(strInput[i]);
			}

			//  // Decrypting: we can reuse the same object
			unsigned char output[255];
			memset(output,0,255);
			Rijndael rin;
		
			rin.init(Rijndael::CBC,Rijndael::Decrypt, key, Rijndael::Key32Bytes);
			int len = rin.padDecrypt(inText, nDecryptLen, output);
			if(len >= 0)
			{
				strReturn = output;
			}
			//  else decryptError(len);
		}

	}
	catch(...)
	{
	//	cout << roException.what() << endl;
	}
	return strReturn;
}