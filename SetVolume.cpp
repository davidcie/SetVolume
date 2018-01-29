/**

  Copyright (c) 2016, Dawid Ciecierski

  Based on and inspired by code shared by Larry Osterman of Microsoft at
  https://blogs.msdn.microsoft.com/larryosterman/2007/03/06/how-do-i-change-the-master-volume-in-windows-vista/

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#define WINVER       _WIN32_WINNT_VISTA
#define _WIN32_WINNT _WIN32_WINNT_VISTA

#define VERSION_MAJOR 2
#define VERSION_MINOR 0

#include <cstdio>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

void DisplayUsageAndExit()
{
	printf("SetVolume v%d.%d\n", VERSION_MAJOR, VERSION_MINOR);
	printf("Usage: \n");
	printf(" SetVolume get            Reports current default playback device volume as a percentage.\n");
	printf(" SetVolume set <percent>  Sets current default playback device volume in percentage.\n");
	printf(" SetVolume set +<percent> Increases default playback device volume by a specified percentage.\n");
	printf(" SetVolume set -<percent> Decreases default playback device volume by a specified percentage.\n");
	exit(-1);
}

void SetVolume(IAudioEndpointVolume *endpoint, float volume)
{
	HRESULT hr;

	printf("Setting volume to: %.0f%%\n", volume * 100);
	hr = endpoint->SetMasterVolumeLevelScalar(volume, nullptr);
	if (hr != S_OK) {
		printf("Unable to set master volume (error code: 0x%08lx)\n", hr);
		endpoint->Release();
		CoUninitialize();
		exit(-1);
	}
}

float GetVolume(IAudioEndpointVolume *endpoint)
{
	HRESULT hr;
	float volume = 0;

	hr = endpoint->GetMasterVolumeLevelScalar(&volume);
	if (hr != S_OK) {
		printf("Unable to get master volume (error code: 0x%08lx)\n", hr);
		endpoint->Release();
		CoUninitialize();
		exit(-1);
	}
	return volume;
}

int main(int argc, CHAR* argv[])
{
	HRESULT hr;
	float newVolume = 0;

	// Exit early if only displaying help
	if (argc == 1 || argc > 1 && strcmp(argv[1], "help") == 0) {
		DisplayUsageAndExit();
	}

	// Initialize the COM library
	CoInitialize(nullptr);

	// Get audio device enumerator
	IMMDeviceEnumerator *deviceEnumerator = nullptr;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	if (hr != S_OK) {
		printf("Unable to create instance of MMDeviceEnumerator (error code: 0x%08lx)\n", hr);
		CoUninitialize();
		exit(-1);
	}

	// Ask device enumerator for the default audio renderer
	IMMDevice *defaultDevice = nullptr;
	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = nullptr;
	if (hr != S_OK) {
		printf("Unable to get default audio endpoint (error code: 0x%08lx)\n", hr);
		CoUninitialize();
		exit(-1);
	}
	
	// Ask default audio renderer for volume controller
	IAudioEndpointVolume *endpointVolume = nullptr;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = nullptr;
	if (hr != S_OK) {
		printf("Unable to get default audio volume controller (error code: 0x%08lx)\n", hr);
		CoUninitialize();
		exit(-1);
	}

	// Parse command line arguments and perform actions
	if (argc == 2 && strcmp(argv[1], "get") == 0)
	{
		printf("%.0f\n", GetVolume(endpointVolume) * 100);
	} else if (argc == 3 && strcmp(argv[1], "set") == 0) {
		newVolume = strtof(argv[2], nullptr) / 100;

		if (argv[2][0] == '+' || argv[2][0] == '-') {
			newVolume += GetVolume(endpointVolume);
		}

		if (newVolume < 0) newVolume = 0;
		if (newVolume > 1) newVolume = 1;
		SetVolume(endpointVolume, newVolume);
	}

	// Release resources
	endpointVolume->Release();
	CoUninitialize();

	return 0;
}