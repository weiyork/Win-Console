#include "StdAfx.h"
#include "RecordingLight.h"
#include "DelcomDLL.h"
#include <vector>

typedef DWORD (*FnDelcomScanDevices)( DWORD, DeviceNameStruct[], DWORD );

CRecordingLight *CRecordingLight::s_instance = NULL;

CRecordingLight::CRecordingLight(void)
{
	m_hLight = NULL;
}

CRecordingLight::~CRecordingLight(void)
{
	StopRecording();
	Close();
}

CRecordingLight *CRecordingLight::GetInstance()
{
	if(!s_instance)
	{
		s_instance = new CRecordingLight();
		s_instance->Init();
		s_instance->StopRecording();
	}

	return s_instance;
}

BOOL CRecordingLight::Init()
{
	try
	{
		DWORD Result=0;
		char DeviceName[MaxDeviceLen];

		int i=0;
		for(; i<20; i++)
		{
			Result = DelcomGetNthDevice(i, 0, DeviceName);
			if(Result)
				break;
		}
		if(Result==0)
			return FALSE;

		m_hLight = DelcomOpenDevice(DeviceName,0);	// open device

		if(!m_hLight)
			return FALSE;

		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CRecordingLight::StartRecording()
{
	try
	{
		signed char c =1;	//0: off 1:on, 2: flash

		DelcomLEDControl(m_hLight, GREENLED,c);
		DelcomLEDControl(m_hLight, REDLED,c);
		DelcomLEDControl(m_hLight, BLUELED,c);
		//	return FALSE;
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CRecordingLight::StopRecording()
{
	try
	{
		signed char c =0;	//0: off 1:on, 2: flash

		DelcomLEDControl(m_hLight, GREENLED,c);
		DelcomLEDControl(m_hLight, REDLED,c);
		DelcomLEDControl(m_hLight, BLUELED,c);

		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}



BOOL CRecordingLight::SetAlarm()
{
	try
	{
		signed char c =2;	//0: off 1:on, 2: flash

		DelcomLEDControl(m_hLight, GREENLED,c);
		DelcomLEDControl(m_hLight, REDLED,c);
		DelcomLEDControl(m_hLight, BLUELED,c);
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CRecordingLight::Close()
{
	try
	{
		signed char c =1;	//0:on 1:off

		if(DelcomCloseDevice(m_hLight)==0)
			return FALSE;

		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}	

