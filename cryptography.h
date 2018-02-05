// cryptography.h: interface for the Cryptography class.
//
//Support DES(1),AES_128(14),AES_192(15),AES_256(16), IDs see wincrypt.h

#if !defined(AFX_CRYPTOGRAPHY_H__38B78D05_AEC4_4AEF_9B53_19342CE16279__INCLUDED_)
#define AFX_CRYPTOGRAPHY_H__38B78D05_AEC4_4AEF_9B53_19342CE16279__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <wincrypt.h>

typedef struct _CryptAPIKeyStruct
{
    BLOBHEADER Header;
    DWORD dwKeyLength;
    BYTE cbKey[32];
}  _CryptAPIKeyStruct;


class SymmetricCryptography  
{
public:
	int Decrypt(BYTE *Text, int Length);
	int Encrypt(BYTE *Text, int Length);
	int SetKey(const BYTE *Key);
	const char* GetErrorMessage(DWORD dwError);
//	SymmetricCryptography();
	virtual ~SymmetricCryptography();
	SymmetricCryptography(int AlgorithmID = 0);
	int GenRandom(BYTE *Text,DWORD dwLen);

private:
	int _AlgorithmID;
	HCRYPTPROV hCryptProvHandle; 
	HCRYPTKEY hKeyHandle; 

};



#endif // !defined(AFX_CRYPTOGRAPHY_H__38B78D05_AEC4_4AEF_9B53_19342CE16279__INCLUDED_)
