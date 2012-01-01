#include <windows.h>
#include "trace.h"

#define CC __stdcall

DWORD (CC *o_XLiveInitializeEx)(void*,DWORD) = NULL;
DWORD (CC *o_XLiveUnprotectData)(BYTE*,DWORD,BYTE*,DWORD*,HANDLE) = NULL;


extern "C" DWORD CC XLiveInitializeEx(void* unk_struct, DWORD ver)
{
	trace("XLiveInitializeEx(%p, %d)\n", unk_struct, ver);

	DWORD ret = o_XLiveInitializeEx(pxi, ver);

	trace("    return: %d\n", ret);
	if (unk_struct) {
		trace("    unk_struct:\n");
		tracebuf((BYTE *)unk_struct, 512);
	}

	return ret;
}


extern "C"  DWORD CC XLiveUnprotectData (BYTE* in_buffer, DWORD in_buffer_size, BYTE* out_buffer, DWORD* out_buffer_size, HANDLE* handle)
{
	trace("XLiveUnprotectData\n");
	trace("    in_buffer_size = %d\n", in_buffer_size);
	if (in_buffer == NULL)
		trace("    in_buffer == NULL\n");
	else {
		trace("    in_buffer =\n");
		tracebuf(in_buffer, in_buffer_size);
	}
	trace("    out_buffer = %p\n", out_buffer);
	trace("    out_buffer_size = %p\n", out_buffer_size);
	if (out_buffer_size)
		trace("    *out_buffer_size = %d\n", *out_buffer_size);
	trace("    handle = %p\n", handle);

	DWORD ret = o_XLiveUnprotectData(in_buffer, in_buffer_size, out_buffer, out_buffer_size, handle);

	trace("    return value: %d\n", ret);

	// after call
	if (out_buffer_size)
		trace("    *out_buffer_size = %d\n", *out_buffer_size);
	if (out_buffer) {
		trace("    out_buffer =\n");
		tracebuf(out_buffer, *out_buffer_size);
	}
	trace("handle = %p\n", handle);

	return ret;
}


void inject(DWORD addr, DWORD local_function)
{
	// make addr writable
	DWORD protection;
	VirtualProtect((LPVOID)addr, 5, PAGE_EXECUTE_READWRITE, &protection);

	// replace target addr with JMP to local function
	BYTE *mem = (BYTE *)addr;
	mem[0] = 0xe9;
	DWORD relative = local_function - (addr + 5);
	*(DWORD *)(mem[1]) = relative;

	// restore
	VirtualProtect((LPVOID)addr, 5, protection, &protection);
}


void xlive_tracer_open()
{
	trace_open();

	HINSTANCE hDLL = LoadLibrary("xlive.dll");
	o_XLiveInitializeEx = (DWORD (CC *)(void*,DWORD))GetProcAddress(hDLL, (PCHAR)LOWORD(5297));
	o_XLiveUnprotectData = (DWORD (CC *)(BYTE*,DWORD,BYTE*,DWORD*,HANDLE))GetProcAddress(hDLL, (PCHAR)LOWORD(5035));

	// patch code
#define PATCH(addr, function) inject((addr), (DWORD)(function));
	#include "patch.h"
}


void xlive_tracer_close()
{
	trace_close();
}
