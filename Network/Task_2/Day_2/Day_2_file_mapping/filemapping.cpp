#include"filemapping.h"
#include <assert.h>

#ifdef _WIN32

#include <strsafe.h>

void ErrorExit(const TCHAR *);

FileMappingBlock::FileMappingBlock():addr(NULL), base(NULL), size(0) {}
FileMappingBlock::~FileMappingBlock() {
    if (addr) UnmapViewOfFile(addr);
}
size_t FileMappingBlock::offset() {
    return (size_t)((unsigned char*)base - (unsigned char*)addr);
}

FileMappingReader::FileMappingReader(const TCHAR *fileName) : hFileMap(NULL) {
    // File
    HANDLE hFile = CreateFile(fileName,
        GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, 
        FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        ErrorExit(TEXT("CreateFile"));
    }
    // File mapping
    // After creating file mapping, its handle will be closed in destructor.
    hFileMap = CreateFileMapping(hFile, 
        NULL, PAGE_READONLY,
        0, 0, NULL);

    if (!hFileMap) {
        ErrorExit(TEXT("CreateFileMapping"));
    }

    // File Size
    DWORD dwFileSizeHigh;
    qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
    qwFileSize += ( ((uint64_t)dwFileSizeHigh) << 32 );

    // Close the file handle.
    CloseHandle(hFile);

    // System info
    GetSystemInfo(&sysInfo);

}


FileMappingReader::~FileMappingReader() {
    if (hFileMap) CloseHandle(hFileMap);
}

void FileMappingReader::readBytes(void* buffer, uint64_t offset, uint64_t nBytes) {
    assert(buffer && "'buffer' is null pointer.");
    uint64_t qwBufferSize = nBytes, qwFileOffset = offset;
    DWORD dwMapOffset = 0;

    if (qwFileOffset > 0) {
        dwMapOffset = qwFileOffset % sysInfo.dwAllocationGranularity;
        qwFileOffset -= dwMapOffset;
    }

    while (qwBufferSize > 0) {
        DWORD dwBytes = sysInfo.dwAllocationGranularity;

        if (dwMapOffset) qwBufferSize += dwMapOffset;
        if (qwBufferSize < dwBytes) dwBytes = (DWORD)qwBufferSize;

        PBYTE pbMap = (PBYTE) MapViewOfFile( hFileMap,
            FILE_MAP_READ,
            (DWORD)(qwFileOffset >> 32),
            (DWORD)(qwFileOffset & 0xffffffff),
            dwBytes );
        
        if (!pbMap) ErrorExit(TEXT("MapViewOfFile"));
        assert(pbMap);

        memcpy((char*)buffer, (pbMap + dwMapOffset), (dwBytes - dwMapOffset));
        buffer = (unsigned char*)buffer + dwBytes - dwMapOffset;

        UnmapViewOfFile(pbMap);

        if (dwMapOffset) dwMapOffset = 0;
        qwFileOffset += dwBytes;
        qwBufferSize -= dwBytes;
    }

}


void FileMappingReader::map(uint64_t offset, uint64_t nBytes, FileMappingBlock *block) {
    assert(block && "'block' is null pointer.");
    uint64_t qwBufferSize = nBytes, qwFileOffset = offset;
    DWORD dwMapOffset = 0;

    if (qwFileOffset > 0) {
        dwMapOffset = qwFileOffset % sysInfo.dwAllocationGranularity;
        qwFileOffset -= dwMapOffset;
    }

    if (dwMapOffset) qwBufferSize += dwMapOffset;
    DWORD dwBytes = (DWORD) qwBufferSize;

    PBYTE pbMap = (PBYTE)MapViewOfFile(hFileMap,
        FILE_MAP_READ,
        (DWORD)(qwFileOffset >> 32),
        (DWORD)(qwFileOffset & 0xffffffff),
        dwBytes);

    if (!pbMap) ErrorExit(TEXT("MapViewOfFile"));
    assert(pbMap);

    block->addr = pbMap;
    block->base = (unsigned char*)block->addr + dwMapOffset;
    block->size = dwBytes;

}



uint64_t FileMappingReader::fileSize() {
    return qwFileSize;
}
#else

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void errExit(const TCHAR *);


FileMappingBlock::FileMappingBlock():addr(NULL), base(NULL),size(0) {}

FileMappingBlock::~FileMappingBlock(){
    if(addr) munmap(addr, size);
}

size_t FileMappingBlock::offset(){
    return (size_t)((unsigned char *)base - (unsigned char *)addr);
}

FileMappingReader::FileMappingReader(const TCHAR *fileName): fd(-1) {
    fd = open(fileName, O_RDWR);
    if(fd == -1) errExit("open");
    
    struct stat sb;
    if(fstat(fd, &sb) == -1) errExit("fstat");
    fsz = sb.st_size;

    pgsz = sysconf(_SC_PAGE_SIZE);
}


FileMappingReader::~FileMappingReader(){
    if(fd != -1) close(fd);
}


void FileMappingReader::readBytes(void *buffer, uint64_t offset, uint64_t nBytes){
    assert(buffer && "'buffer' is null pointer.");
    uint64_t bfsz = nBytes;         // buffer size
    off_t fofst = (off_t) offset;   // file offset
    uint64_t mofst = 0;             // map offset

    if(fofst > 0){
        mofst = fofst % pgsz;
        fofst -= mofst;
    }

    while(bfsz > 0){
        size_t bsz = pgsz;
        if(mofst) bfsz += mofst;
        if(bfsz < bsz){
            bsz = bfsz;
        }

        unsigned char *addr = (unsigned char *) mmap( NULL, bsz, 
            PROT_READ, MAP_PRIVATE, 
            fd, fofst );
        if(addr == MAP_FAILED ) errExit("mmap");

        memcpy(buffer, addr + mofst, bsz - mofst);
        buffer = (unsigned char *)buffer + bsz - mofst;
        munmap(addr, bsz);

        if(mofst) mofst = 0;
        fofst += bsz;
        bfsz -= bsz;
    }
}


void FileMappingReader::map(uint64_t offset, uint64_t nBytes, FileMappingBlock *block){
    assert(block && "'block' is null pointer.");
    uint64_t bfsz = nBytes;         // buffer size
    off_t fofst = (off_t) offset;   // file offset
    uint64_t mofst = 0;             // map offset

    if(fofst > 0){
        mofst = fofst % pgsz;
        fofst -= mofst;
    }

    if(mofst) bfsz += mofst;
    size_t bsz = (size_t)bfsz;

    unsigned char *addr = (unsigned char *) mmap( NULL, bsz, 
        PROT_READ, MAP_PRIVATE, 
        fd, fofst );
    if(addr == MAP_FAILED ) errExit("mmap");

    block->addr = addr;
    block->base = addr + mofst;
    block->size = bsz;

}

uint64_t FileMappingReader::fileSize(){
    return fsz;
}

#endif