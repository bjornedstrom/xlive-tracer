#include <windows.h>
#include <stdlib.h>

#include "trace.h"

CRITICAL_SECTION lock;
static FILE *logfile;

void trace(char* msg, ...)
{
	EnterCriticalSection (&lock);
	va_list	arg;
	va_start (arg, message);
	vfprintf (logfile, message, arg);
	LeaveCriticalSection (&lock);
}

void tracebuf(BYTE *buf, DWORD sizet)
{
	int i = 0;
	char line[128];
	line[0] = 0;
	for (i = 0; i < sizet; i++) {
		char smallbuf[64];
		sprintf(smallbuf, "%02x ", buf[i]);
		strcat(line, smallbuf);

		if ((i == (sizet-1)) || ((i > 0) && ((i % 16) == 0))) {
			strcat(line, "\n");
			trace(line);
			line[0] = 0;
		}
	}
}

void trace_open()
{
	logfile = fopen("xlive.trace", "at");
	InitializeCriticalSection (&lock);
}

void trace_close()
{
	EnterCriticalSection(&lock);
	fflush(logfile);
	fclose(logfile);
	logfile = NULL;
	LeaveCriticalSection(&lock);
	DeleteCriticalSection(&lock);
}
