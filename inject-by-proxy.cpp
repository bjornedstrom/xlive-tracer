#include <windows.h>
#include "xlive-tracer.h"

#define CC __stdcall

void* (CC *o_resample_open)(int, double, double) = NULL;
void  (CC *o_resample_close)(void*) = NULL;
int   (CC *o_resample_process)(void*,double,float*,int,int,int*,float*,int) = NULL;
void* (CC *o_resample_dup)(void*) = NULL;
int   (CC *o_resample_get_filter_width)(void*) = NULL;

extern "C" void* CC resample_open(int      highQuality,
                    double   minFactor,
                    double   maxFactor)
{
	return o_resample_open(highQuality, minFactor, maxFactor);
}

extern "C" void* CC resample_dup(const void *handle)
{
	return o_resample_dup((void *)handle);
}

extern "C" int  CC resample_get_filter_width(const void *handle)
{
	return o_resample_get_filter_width((void *)handle);
}

extern "C" int CC resample_process(void   *handle,
                     double  factor,
                     float  *inBuffer,
                     int     inBufferLen,
                     int     lastFlag,
                     int    *inBufferUsed,
                     float  *outBuffer,
                     int     outBufferLen)
{
	return o_resample_process(handle, factor, inBuffer, inBufferLen, lastFlag, inBufferUsed, outBuffer, outBufferLen);
}

extern "C" void CC resample_close(void *handle)
{
	o_resample_close(handle);
}


void load()
{
	HINSTANCE hDLL = LoadLibrary("libresample.dll");
	o_resample_open = (void* (CC *)(int, double, double))GetProcAddress(hDLL, "resample_open");
	o_resample_close = (void (CC *)(void*))GetProcAddress(hDLL, "resample_close");
	o_resample_process = (int (CC *)(void*,double,float*,int,int,int*,float*,int))GetProcAddress(hDLL, "resample_process");
	o_resample_dup = (void* (CC *)(void*))GetProcAddress(hDLL, "resample_dup");
	o_resample_get_filter_width = (int (CC *)(void*))GetProcAddress(hDLL, "resample_get_filter_width");
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD reason, LPVOID lpReserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		load();
		xlive_tracer_open();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		xlive_tracer_close();
		break;
	}
    return TRUE;
}
