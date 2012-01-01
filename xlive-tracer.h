extern "C" DWORD CC XLiveInitializeEx(void* unk_struct, DWORD ver);
extern "C"  DWORD CC XLiveUnprotectData (BYTE* in_buffer, DWORD in_buffer_size, BYTE* out_buffer, DWORD* out_buffer_size, HANDLE* handle);

void xlive_tracer_open();
void xlive_tracer_close();
