#include "stdafx.h"

#include "SMPDBSecurity.h"
#include "cryptography.h"

#define ENC_KEY "TR@#$#Wry$@1234FDT^%&7895Gfn<>zx"

CSMPDBSecurity::CSMPDBSecurity() 
{
}

CSMPDBSecurity::~CSMPDBSecurity()
{
}




BOOL CSMPDBSecurity::DecryptPassword( const CByteArray &byteArray, CString &csDecryptedPassword )
{
	BOOL bReturn = FALSE;
	try
	{
		SymmetricCryptography crypt(ALG_SID_AES_256);
		CString csKey = ENC_KEY;
		if( crypt.SetKey( (BYTE *)csKey.GetBuffer(0) )==0 )
		{
			int nLength = byteArray.GetSize();
			
			BYTE *pByteBuffer = new BYTE[nLength];
			memset(pByteBuffer,0,nLength);
			if( pByteBuffer )
			{
				int i = 0;
				for(i=0;i<nLength;i++ )
				{
					pByteBuffer[i] = byteArray.GetAt(i);
				}
				if( crypt.Decrypt( (BYTE *)pByteBuffer, nLength ) == 0 )
				{
					int nDecryptedLength = pByteBuffer[0];
					if( nDecryptedLength > 0  && nDecryptedLength+1<nLength )
					{
						for( i=0;i<nDecryptedLength;i++ )
						{
							csDecryptedPassword += (char)pByteBuffer[i+1];
						}
						bReturn = TRUE;
					}
					else
					{
						csDecryptedPassword = "";
						bReturn = FALSE;
					}

				}
				delete pByteBuffer;
				pByteBuffer = NULL;
			}
		}
	}
	catch(...)
	{
		csDecryptedPassword = "";
		bReturn = FALSE;
	}
	return TRUE;
}

BOOL CSMPDBSecurity::EncryptPassword( const CString &csDecryptedPassword, CByteArray &byteArray )
{
	BOOL bReturn = FALSE;
	try
	{
		SymmetricCryptography crypt(ALG_SID_AES_256);
		CString csKey = ENC_KEY;
		if( crypt.SetKey( (BYTE *)csKey.GetBuffer(0) )==0 )
		{
			int nLength = csDecryptedPassword.GetLength();
			CString csEncryptedPassword = "";
			csEncryptedPassword = char(nLength) + csDecryptedPassword;
			nLength++;
			//The string must be multiples of 32 long
			while( nLength % 32 != 0 )
			{
				csEncryptedPassword += " ";
				nLength = csEncryptedPassword.GetLength();
			}
			
			BYTE *pByteBuffer = new BYTE[nLength];
			memset(pByteBuffer,0,nLength);

			if( pByteBuffer )
			{
				memcpy( pByteBuffer, csEncryptedPassword.GetBuffer(0), nLength );
				if( crypt.Encrypt( (BYTE *)pByteBuffer, nLength )==0 )
				{
					int i = 0;
					for( i=0;i<nLength;i++ )
					{
						byteArray.Add(pByteBuffer[i]);
					}
					
					bReturn = TRUE;
				}
				delete pByteBuffer;
				pByteBuffer = NULL;
			}
		}
	}
	catch(...)
	{
		byteArray.RemoveAll();
		bReturn = FALSE;
	}
	return TRUE;
}



