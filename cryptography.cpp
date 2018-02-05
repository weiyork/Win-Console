// cryptography.cpp: implementation of the Cryptography class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cryptography.h"
#include <memory.h>
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SymmetricCryptography::~SymmetricCryptography()
{
	if(hKeyHandle) 
	{
		CryptDestroyKey(hKeyHandle); 
	}

	hKeyHandle = 0;

	if(hCryptProvHandle) 
	{
		CryptReleaseContext(hCryptProvHandle, 0);
	}
	
	hCryptProvHandle = 0;

}
SymmetricCryptography::SymmetricCryptography(int AlgorithmID)
{
	// we should check to see if we need to delete them first 
	// MAV March 26 2011
	if(hKeyHandle) 
	{
		CryptDestroyKey(hKeyHandle); 
	}

	hKeyHandle = 0;

	if(hCryptProvHandle) 
	{
		CryptReleaseContext(hCryptProvHandle, 0);
	}
	// MAV March 26 2011 - end of change
	hCryptProvHandle = 0;
	hCryptProvHandle = 0;
	hKeyHandle = 0;

	CString csError;
	CString csAcquireSyntax;
	CString csErrorFormat = "###LIC### \nThreadID: %d %s  Return Error: %d SystemError: %d\n";

	int iErr = 0;

	if (AlgorithmID == 0)
	{
		_AlgorithmID = ALG_SID_AES_128;
	}
	else
	{
		_AlgorithmID = AlgorithmID;
	}

	switch (_AlgorithmID)
	{
		case ALG_SID_AES_128:
		case ALG_SID_AES_192:
		case ALG_SID_AES_256:
			iErr = CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider", PROV_RSA_AES, 0);
			csAcquireSyntax = "CryptAcquireContext(&hCryptProvHandle, NULL, \"Microsoft Enhanced RSA and AES Cryptographic Provider\", PROV_RSA_AES, 0)";

			if (!iErr)
			{
				csError.Format(csErrorFormat,GetCurrentThreadId(),  csAcquireSyntax, iErr, GetLastError());
				OutputDebugString(csError);

				iErr = CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider",PROV_RSA_AES, CRYPT_NEWKEYSET);
				csAcquireSyntax = "CryptAcquireContext(&hCryptProvHandle, NULL, \"Microsoft Enhanced RSA and AES Cryptographic Provider\" PROV_RSA_AES, CRYPT_NEWKEYSET))";

				if (!iErr)
				{
					csError.Format(csErrorFormat,GetCurrentThreadId(),  csAcquireSyntax, iErr, GetLastError());
					OutputDebugString(csError);

					iErr = CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider", PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
					csAcquireSyntax = "CryptAcquireContext(&hCryptProvHandle, NULL, \"Microsoft Enhanced RSA and AES Cryptographic Provider\", PROV_RSA_AES, CRYPT_VERIFYCONTEXT))";

					if (!iErr)
					{
						csError.Format(csErrorFormat,GetCurrentThreadId(),  csAcquireSyntax, iErr, GetLastError());
						OutputDebugString(csError);
	
						iErr = CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",PROV_RSA_AES,0);
						csAcquireSyntax = "CryptAcquireContext(&hCryptProvHandle, NULL, \"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)\",PROV_RSA_AES,0)";

						if (!iErr)
						{
							csError.Format(csErrorFormat,GetCurrentThreadId(),  csAcquireSyntax, iErr, GetLastError());
							OutputDebugString(csError);

							iErr = CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
							csAcquireSyntax = "CryptAcquireContext(&hCryptProvHandle, NULL, \"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)\",PROV_RSA_AES, CRYPT_VERIFYCONTEXT)";

							if (!iErr)
							{
								csError.Format(csErrorFormat,GetCurrentThreadId(),  csAcquireSyntax, iErr, GetLastError());
								OutputDebugString(csError);

								iErr = CryptAcquireContext(&hCryptProvHandle, NULL,"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",PROV_RSA_AES, CRYPT_NEWKEYSET);
								csAcquireSyntax = "CryptAcquireContext(&hCryptProvHandle, NULL,\"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)\",PROV_RSA_AES, CRYPT_NEWKEYSET)";

								if (!iErr)
								{
									csError.Format(csErrorFormat,GetCurrentThreadId(),  csAcquireSyntax, iErr, GetLastError());
									OutputDebugString(csError);

									hCryptProvHandle = 0;
								}
							}
						}
					}
				}
			}

			break;

		case ALG_SID_DES:
			if (!CryptAcquireContext(
				    &hCryptProvHandle, 
				    NULL,
				    MS_ENHANCED_PROV, 
					PROV_RSA_FULL,
					0))
			{
				hCryptProvHandle = 0;
		    }
			break;
	}
}
/*
SymmetricCryptography::SymmetricCryptography(int AlgorithmID)
{
	hCryptProvHandle = 0;
	hKeyHandle = 0;

	if (AlgorithmID == 0)
		_AlgorithmID = ALG_SID_AES_128;
	else
		_AlgorithmID = AlgorithmID;

	switch (_AlgorithmID)
	{
		case ALG_SID_AES_128:
		case ALG_SID_AES_192:
		case ALG_SID_AES_256:
			if (!CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider", 
				PROV_RSA_AES, 0))
			{
				if (!CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider",
					PROV_RSA_AES, CRYPT_NEWKEYSET))
				{
					if (!CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider",
						PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
					{
						if (!CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",
							PROV_RSA_AES,0))
						{
							if (!CryptAcquireContext(&hCryptProvHandle, NULL, "Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",
								PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
							{
								if (!CryptAcquireContext(&hCryptProvHandle, NULL,"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",
									PROV_RSA_AES, CRYPT_NEWKEYSET))
								{
									hCryptProvHandle = 0;
								}
							}
						}
					}
				}
			}

			break;

		case ALG_SID_DES:
			if (!CryptAcquireContext(
				    &hCryptProvHandle, 
				    NULL,
				    MS_ENHANCED_PROV, 
					PROV_RSA_FULL,
					0))
			{
				hCryptProvHandle = 0;
		    }
			break;
	}
}


SymmetricCryptography::SymmetricCryptography(int AlgorithmID)
{
	hCryptProvHandle = 0;
	hKeyHandle = 0;

	if (AlgorithmID == 0)
		_AlgorithmID = ALG_SID_AES_128;
	else
		_AlgorithmID = AlgorithmID;

	switch (_AlgorithmID)
	{
		case ALG_SID_AES_128:
		case ALG_SID_AES_192:
		case ALG_SID_AES_256:
			if (!CryptAcquireContext(
				    &hCryptProvHandle, 
				    NULL,
				    "Microsoft Enhanced RSA and AES Cryptographic Provider",
				    PROV_RSA_AES,
					0))
			if (!CryptAcquireContext(
				    &hCryptProvHandle, 
				    NULL,
				    "Microsoft Enhanced RSA and AES Cryptographic Provider",
				    PROV_RSA_AES,
					CRYPT_NEWKEYSET))
			if (!CryptAcquireContext(
				    &hCryptProvHandle, 
				    NULL,
				    "Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",
				    PROV_RSA_AES,
					0))
			if (!CryptAcquireContext(
				    &hCryptProvHandle, 
				    NULL,
				    "Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)",
				    PROV_RSA_AES,
					CRYPT_NEWKEYSET))
			{
				hCryptProvHandle = 0;
		    }
			break;

		case ALG_SID_DES:
			if (!CryptAcquireContext(
				    &hCryptProvHandle, 
				    NULL,
				    MS_ENHANCED_PROV, 
					PROV_RSA_FULL,
					0))
			{
				hCryptProvHandle = 0;
		    }
			break;
	}
}
*/
//Init a User KEY
//Length should be 32*n (in byte)
int SymmetricCryptography::SetKey(const BYTE *UserKey)
{
    int KeyStructureSize;
	_CryptAPIKeyStruct KeyStruct;
	DWORD dwMode = CRYPT_MODE_ECB ;

	if(UserKey == NULL) 
		return ERROR_INVALID_PARAMETER;
	if(!hCryptProvHandle)
		return ERROR_INVALID_PARAMETER;
	if(hKeyHandle) 
		CryptDestroyKey(hKeyHandle); 
	hKeyHandle = 0;

	switch (_AlgorithmID)
	{
		case ALG_SID_AES_128:
		case ALG_SID_AES_192:
		case ALG_SID_AES_256:

			memset(&KeyStruct,0,sizeof(KeyStruct));
            KeyStruct.Header.bType = PLAINTEXTKEYBLOB;
            KeyStruct.Header.bVersion = CUR_BLOB_VERSION;
            KeyStruct.Header.reserved = 0;

			if (_AlgorithmID == ALG_SID_AES_128)
			{
				KeyStructureSize = sizeof(KeyStruct) - 16;
				KeyStruct.Header.aiKeyAlg = CALG_AES_128;
				KeyStruct.dwKeyLength = 16;
			}
			else if (_AlgorithmID == ALG_SID_AES_192) 
			{
				KeyStructureSize = sizeof(KeyStruct) - 8;
	            KeyStruct.Header.aiKeyAlg = CALG_AES_192;
		        KeyStruct.dwKeyLength = 24;
			}
			else if (_AlgorithmID == ALG_SID_AES_256) 
			{
				KeyStructureSize = sizeof(KeyStruct);
	            KeyStruct.Header.aiKeyAlg = CALG_AES_256;
		        KeyStruct.dwKeyLength = 32;
			}

			memcpy( KeyStruct.cbKey,  UserKey, KeyStruct.dwKeyLength );

			if(!CryptImportKey(hCryptProvHandle, (CONST BYTE*)&KeyStruct, KeyStructureSize, NULL, 0, &hKeyHandle ) ) 
			{
				return GetLastError();
		    }

			if(!CryptSetKeyParam(hKeyHandle, KP_MODE, (BYTE*)&dwMode, 0)) 
			{
				return GetLastError();
			}		

			break;

		case ALG_SID_DES:

			memset(&KeyStruct,0,sizeof(KeyStruct));
            KeyStruct.Header.bType = PLAINTEXTKEYBLOB;
            KeyStruct.Header.bVersion = CUR_BLOB_VERSION;
            KeyStruct.Header.reserved = 0;
			KeyStructureSize = sizeof(KeyStruct) - 24;
			KeyStruct.Header.aiKeyAlg = CALG_DES;
			KeyStruct.dwKeyLength = 8;
			memcpy( KeyStruct.cbKey,  UserKey, KeyStruct.dwKeyLength );

			if(!CryptImportKey(hCryptProvHandle, (CONST BYTE*)&KeyStruct, KeyStructureSize, NULL, 0, &hKeyHandle ) ) 
			{
				return GetLastError();
			}		

			if(!CryptSetKeyParam(hKeyHandle, KP_MODE, (BYTE*)&dwMode, 0)) 
			{
				return GetLastError();
			}		
			break;

		default:
			return ERROR_INVALID_PARAMETER;

	}

	return 0;
}


//Encrypt Text (Plain) into Text (Cipher)
//
//The length (bytes) of Text should be 32*n (in byte), 
//    so that the program works even if cipher algorithm varies from 64 bit to 256 bit.
//
//About padding
//PlainText should be padded to 32*n bytes.
//
//C style string: 
//   if strings can contain 32*n character, it must be padded to 32*(n+1) bytes,
//   else the decrypted data will not contain terminal character '\0x00', 
//   and string functions may not work properly.
//
//Object should be serialized into BYTE ARRAY
//
int SymmetricCryptography::Encrypt(BYTE *Text, int Length)
{
	DWORD d = (DWORD)Length;

	if(hKeyHandle == 0) 
		return ERROR_INVALID_PARAMETER;
	if(hCryptProvHandle == 0)
		return ERROR_INVALID_PARAMETER;

	switch (_AlgorithmID)
	{
		case ALG_SID_AES_128:
		case ALG_SID_AES_192:
		case ALG_SID_AES_256:
		case ALG_SID_DES:

			if(!CryptEncrypt( hKeyHandle, NULL, FALSE, 0, (unsigned char*)Text, &d, (DWORD)Length ))
			{
				return GetLastError();
			}		
			if (d != (DWORD)Length)
			{
				return ERROR_INVALID_PARAMETER;
			}
			break;

		default:
			return ERROR_INVALID_PARAMETER;

	}
	return 0;
 
}

//Decrypt CipherText to PlainText, reverse function for Encrypt
//Requirements for CipherText,PlainText,Length are same as Encrypt 
int SymmetricCryptography::Decrypt(BYTE *Text, int Length)
{
	DWORD d = (DWORD)Length;

	if(hKeyHandle == 0) 
		return ERROR_INVALID_PARAMETER;
	if(hCryptProvHandle == 0)
		return ERROR_INVALID_PARAMETER;

	switch (_AlgorithmID)
	{
		case ALG_SID_AES_128:
		case ALG_SID_AES_192:
		case ALG_SID_AES_256:
		case ALG_SID_DES:

			if (!CryptDecrypt( hKeyHandle, NULL, FALSE, 0, (unsigned char*)Text, &d ))
			{
				return GetLastError();
			}		
			if (d != (DWORD)Length)
			{
				return ERROR_INVALID_PARAMETER;
			}
			break;

		default:
			return ERROR_INVALID_PARAMETER;
	}

	return 0;
}

//Random data generator
int SymmetricCryptography::GenRandom(BYTE *Text, DWORD dwLen)
{
	if(hCryptProvHandle == 0)
		return ERROR_INVALID_PARAMETER;
	if (!CryptGenRandom(hCryptProvHandle, dwLen, Text))
	{
		return GetLastError();
	}
	
	return 0;
}

//Translate Error Code into String
const char* SymmetricCryptography::GetErrorMessage(DWORD dwError)
{
    switch( dwError )
    {
		case ERROR_ACCESS_DENIED:
			return "ERROR_ACCESS_DENIED";  
		case ERROR_INVALID_HANDLE:
			return "ERROR_INVALID_HANDLE";  
		case ERROR_INVALID_PARAMETER:
			return "ERROR_INVALID_PARAMETER";
		case ERROR_DEV_NOT_EXIST:
			return "ERROR_DEV_NOT_EXIST";
		case NTE_BAD_HASH:
			return "NTE_BAD_HASH";        
		case NTE_BAD_HASH_STATE:
			return "NTE_BAD_HASH_STATE";
		case NTE_BAD_UID:
			return "NTE_BAD_UID";
		case NTE_BAD_KEY:
			return "NTE_BAD_KEY";
		case NTE_BAD_LEN:
			return "NTE_BAD_LEN";
		case NTE_BAD_DATA:
			return "NTE_BAD_DATA";
		case NTE_BAD_VER:
			return "NTE_BAD_VER";
		case NTE_BAD_ALGID:
			return "NTE_BAD_ALGID";
		case NTE_BAD_FLAGS:
			return "NTE_BAD_FLAGS";
		case NTE_BAD_TYPE:
			return "NTE_BAD_TYPE";
		case NTE_BAD_KEY_STATE:
			return "NTE_BAD_KEY_STATE";
		case NTE_NO_KEY:
			return "NTE_NO_KEY";
		case NTE_NO_MEMORY:
			return "NTE_NO_MEMORY";
		case NTE_EXISTS:
			return "NTE_EXISTS";
		case NTE_PERM:
			return "NTE_PERM";
		case NTE_NOT_FOUND:
			return "NTE_NOT_FOUND";
		case NTE_DOUBLE_ENCRYPT:
			return "NTE_DOUBLE_ENCRYPT";
		case NTE_BAD_PROVIDER:
			return "NTE_BAD_PROVIDER";
		case NTE_BAD_PROV_TYPE:
			return "NTE_BAD_PROV_TYPE";
		case NTE_BAD_KEYSET:
			return "NTE_BAD_KEYSET";
		case NTE_PROV_TYPE_NOT_DEF:
			return "NTE_PROV_TYPE_NOT_DEF";
		case NTE_PROV_TYPE_ENTRY_BAD:
			return "NTE_PROV_TYPE_ENTRY_BAD";
		case NTE_KEYSET_NOT_DEF:
			return "NTE_KEYSET_NOT_DEF";
		case NTE_KEYSET_ENTRY_BAD:
			return "NTE_KEYSET_ENTRY_BAD";
		case NTE_BAD_KEYSET_PARAM:
			return "NTE_BAD_KEYSET_PARAM";
		case NTE_FAIL:
			return "NTE_FAIL";
		case NTE_SYS_ERR:
			return "NTE_SYS_ERR";
		case NTE_SILENT_CONTEXT:
			return "NTE_SILENT_CONTEXT";
		case NTE_FIXEDPARAMETER:
			return "NTE_FIXEDPARAMETER";
/*	    case NTE_INVALID_HANDLE:
			return "NTE_INVALID_HANDLE";
		case NTE_INVALID_PARAMETER:
			return "NTE_INVALID_PARAMETER";
		case NTE_BUFFER_TOO_SMALL:
			return "NTE_BUFFER_TOO_SMALL";
		case NTE_BUFFERS_OVERLAP:
			return "NTE_BUFFERS_OVERLAP";
		case NTE_DECRYPTION_FAILURE:
			return "NTE_DECRYPTION_FAILURE";
		case NTE_INTERNAL_ERROR:
			return "NTE_INTERNAL_ERROR";*/
		default: 
			return "Unknown";
    }
}


