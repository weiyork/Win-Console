#pragma once

class CRecordingLight
{

public:
	static CRecordingLight *GetInstance();
	virtual BOOL StartRecording();
	virtual BOOL StopRecording();
	virtual BOOL SetAlarm();

protected:
	CRecordingLight(void);
	virtual ~CRecordingLight(void);

	virtual BOOL Init();
	virtual BOOL Close();

private:
	HMODULE m_hDelcomDLL;
	HANDLE m_hLight;

	static CRecordingLight *s_instance;
};


