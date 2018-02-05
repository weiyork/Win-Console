#ifndef C_SMPDBSECURITY
#define C_SMPDBSECURITY


class CSMPDBSecurity
{
public:
   CSMPDBSecurity();
   ~CSMPDBSecurity();


//protected:
   BOOL DecryptPassword( const CByteArray &byteArray, CString &strDecryptedPassword );
   BOOL EncryptPassword( const CString &strDecryptedPassword, CByteArray &byteArray);

private:

};

#endif