#pragma once
#include <vector>

class CRecordingLight
{

public:
	static CRecordingLight *GetInstance();
	virtual BOOL StartRecording();
	virtual BOOL StopRecording();
	virtual BOOL SetAlarm();
	void GetLightName(vector<CString> &LightNameArray);
	void CheckLightName();

protected:
	CRecordingLight(void);
	virtual ~CRecordingLight(void);

	virtual BOOL Init();
	virtual BOOL Close();

private:
	HMODULE m_hDelcomDLL;
	HANDLE m_hLight;

	vector<CString> m_LightNameArray;

	static CRecordingLight *s_instance;
};


