#include "StdAfx.h"
#include "RecordingLight.h"
#include "DelcomDLL.h"

typedef DWORD (*FnDelcomScanDevices)( DWORD, DeviceNameStruct[], DWORD );
typedef HANDLE (*FnDelcomOpenDevice)( LPSTR, DWORD);
typedef DWORD (*FnDelcomCloseDevice)(HANDLE);
typedef DWORD  (*FnDelcomLEDControl)( HANDLE hFile, DWORD Color, DWORD Mode );

CRecordingLight *CRecordingLight::s_instance = NULL;

CRecordingLight::CRecordingLight(void)
{
	m_hDelcomDLL = NULL;
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
		if( !s_instance->Init() )
		{
			OutputDebugString("VIQ-LIGHT init failed");
		}
		s_instance->StopRecording();
	}

	return s_instance;
}

void CRecordingLight::GetLightName(vector<CString> &LightNameArray)
{
	if(m_LightNameArray.size()>0)
		LightNameArray = m_LightNameArray;
	else
	{
		CheckLightName();
		LightNameArray = m_LightNameArray;
	}
}

void CRecordingLight::CheckLightName()
{
	if( !m_hDelcomDLL )
	{
		m_hDelcomDLL = LoadLibrary("DelcomDLL.dll");
	}

	if( m_hDelcomDLL )
	{
		DWORD dwResult = 0;
		DeviceNameStruct cDeviceNames[10]; // array to hold the device names found  

		FnDelcomScanDevices FnScanDevices = (FnDelcomScanDevices)GetProcAddress(m_hDelcomDLL,"DelcomScanDevices");

		if( FnScanDevices )
		{
			int nFound = FnScanDevices( USBDELVI, cDeviceNames, 10);

			int i=0;

			m_LightNameArray.clear();

			while( i<nFound )
			{
				m_LightNameArray.push_back(cDeviceNames[i].DeviceName);
				i++;
			}
		}
	}
}

BOOL CRecordingLight::Init()
{
	BOOL bReturn = FALSE;
	if( ! m_hDelcomDLL )
	{
		m_hDelcomDLL = LoadLibrary("DelcomDLL.dll");
	}

	if( m_hDelcomDLL )
	{
		DWORD dwResult = 0;
		DeviceNameStruct cDeviceNames[10]; // array to hold the device names found  

		FnDelcomScanDevices FnScanDevices = (FnDelcomScanDevices)GetProcAddress(m_hDelcomDLL,"DelcomScanDevices");
		FnDelcomOpenDevice FnOpenDevice = (FnDelcomOpenDevice)GetProcAddress(m_hDelcomDLL,"DelcomOpenDevice");

		if( FnScanDevices && FnOpenDevice )
		{
			int nFound = FnScanDevices( USBDELVI, cDeviceNames, 10);
			
			if( nFound != 0 )
			{
				m_hLight = FnOpenDevice((char*)&cDeviceNames[0],0);
			}
		}
	}

	if( m_hLight )
	{
		bReturn = TRUE;
	}

	return bReturn;
}

BOOL CRecordingLight::StartRecording()
{
	BOOL bReturn = FALSE;

	OutputDebugString("VIQ-LIGHT1 ControlStation turn light on");

	if( !m_hLight )
		Init();

	if( m_hLight )
	{
		signed char cLightCode = ON;

		FnDelcomLEDControl FNLEDControl = (FnDelcomLEDControl)GetProcAddress(m_hDelcomDLL,"DelcomLEDControl");

		if( FNLEDControl )
		{
			bReturn = FNLEDControl( m_hLight, REDLED, cLightCode );
		}
	}
	else
		OutputDebugString("VIQ-LIGHT failed to turn on light");

	//Close();

	return bReturn;
}

BOOL CRecordingLight::StopRecording()
{
	OutputDebugString("VIQ-LIGHT1 ControlStation turn light off");

	BOOL bReturn = FALSE;

	if( !m_hLight )
		Init();

	if( m_hDelcomDLL && m_hLight )
	{
		signed char cLightCode = OFF;

		FnDelcomLEDControl FNLEDControl = (FnDelcomLEDControl)GetProcAddress(m_hDelcomDLL,"DelcomLEDControl");

		if( FNLEDControl )
		{
			bReturn = FNLEDControl( m_hLight, REDLED, cLightCode );
		}
	}
	else
		OutputDebugString("VIQ-LIGHT failed to turn off light");

	Close();

	return bReturn;
}

BOOL CRecordingLight::SetAlarm()
{
	OutputDebugString("VIQ-LIGHT1 set light alarm");

	if( !m_hLight )
		Init();

	BOOL bReturn = FALSE;

	if( m_hDelcomDLL && m_hLight )
	{
		signed char cLightCode = FLASH;

		FnDelcomLEDControl FNLEDControl = (FnDelcomLEDControl)GetProcAddress(m_hDelcomDLL,"DelcomLEDControl");

		if( FNLEDControl )
		{
			bReturn = FNLEDControl( m_hLight, REDLED, cLightCode );
		}
	}
	else
		OutputDebugString("VIQ-LIGHT failed to set light alarm");

	//Close();

	return bReturn;
}

BOOL CRecordingLight::Close()
{
	BOOL bReturn = FALSE;

	if( m_hDelcomDLL && m_hLight )
	{
		signed char cLightCode = OFF;

		FnDelcomLEDControl FNLEDControl = (FnDelcomLEDControl)GetProcAddress(m_hDelcomDLL,"DelcomLEDControl");
		if( FNLEDControl )
		{
			bReturn = FNLEDControl( m_hLight, REDLED, cLightCode );
		}

		FnDelcomCloseDevice FnCloseDevice = (FnDelcomCloseDevice)GetProcAddress(m_hDelcomDLL,"DelcomCloseDevice");
		if( FnCloseDevice )
		{
			FnCloseDevice(m_hLight);
		}

		m_hLight = NULL;
	}

	if( m_hDelcomDLL )
	{
		FreeLibrary(m_hDelcomDLL);
		m_hDelcomDLL = NULL;
	}

	bReturn = TRUE;
	return bReturn;

}	
