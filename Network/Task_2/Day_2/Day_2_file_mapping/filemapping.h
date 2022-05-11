#ifndef FILE_MAPPING_H_
#define FILE_MAPPING_H_

#include <cstdint>

#ifdef _WIN32

#include <Windows.h>
#include <tchar.h>

#else

#include <fcntl.h>

#define TCHAR char
#define __T(x) x
#define _T(x) __T(x)
#define _TEXT(quote) quote
#define TEXT(quote) _TEXT(quote)

#endif


class FileMappingBlock {
public:
    FileMappingBlock();
    ~FileMappingBlock();
    size_t offset();

    void *addr;
    void *base;
    size_t size;
};


/// Implement the Windows file mapping reader.
class FileMappingReader {
public:
    FileMappingReader(const TCHAR *fileName);
    
    ~FileMappingReader();
    /// Copy bytes to 'buffer'. it begins with 'offset' position, and then read 'nBytes' bytes.
    void readBytes(void* buffer, uint64_t offset, uint64_t nBytes);
    /// Map the file which starts with 'offset' offset and 'nBytes' size to 'block', a virtual memory block.
    void map(uint64_t offset, uint64_t nBytes, FileMappingBlock *block);

    uint64_t fileSize();

protected:

#ifdef _WIN32
    HANDLE hFileMap;        // file mapping handle
    UINT64 qwFileSize;      // file size
    SYSTEM_INFO sysInfo;    // system info
#else
    int fd;                 // file descriptor
    off_t fsz;              // file size
    long pgsz;              // page size

#endif
};

#endif