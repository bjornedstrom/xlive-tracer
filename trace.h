#ifndef TRACE_H
#define TRACE_H

#include <windows.h>

void trace_open();
void trace_close();
void trace(char* msg, ...);
void tracebuf(BYTE* buf, DWORD sizet);

#endif /* TRACE_H */
