#pragma once



class CRecordingLight
{

public:
	static CRecordingLight *GetInstance();
	virtual BOOL StartRecording();
	virtual BOOL StopRecording();
	virtual BOOL SetAlarm();
	virtual BOOL Close();

protected:
	CRecordingLight(void);
	virtual ~CRecordingLight(void);

	virtual BOOL Init();

	

private:

	HANDLE m_hLight;

	static CRecordingLight *s_instance;
};


