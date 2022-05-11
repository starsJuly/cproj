#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

void ErrorExit(LPCTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, PTSTR, int) {

	// Before executing the line below, D:\ does not have
	// a file called "MMFtest.Dat"
	HANDLE hFile = CreateFile( TEXT("MMTest.Dat"), 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL );

	if (hFile == INVALID_HANDLE_VALUE) {
        ErrorExit(TEXT("CreateFile"));
	}
	// Before executing the line below, the MMFTest.Dat
	// file does exist but has a file size of 0 bytes.
	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 
		0, 100, NULL);

    if (!hFileMap) {
        ErrorExit(TEXT("CreateFileMapping"));
    }

	// Aftering executing the line above, the MMFTest.dat
	// file has a size of 100 bytes.
	// Cleanup
	CloseHandle(hFileMap);
	CloseHandle(hFile);

	// When the process terminates, MMFTest.Dat remains
	// on the disk with a size of 100 bytes.
	return (0);
}
