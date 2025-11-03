//      this file is 2 implement hash() by calling into HashDLL.dll @ runtime
#include <windows.h>
#include <stdio.h>
#include "ll.h"     //   4 the prototype: unsigned char* hash(char*, unsigned char*)

typedef unsigned char* (__cdecl* hashfxn)(char*, unsigned char*);

static HMODULE hashdll = NULL;
static hashfxn hashfunc = NULL;

static int loadHashDLL(void) {
    FARPROC p;

    if (hashdll != NULL && hashfunc != NULL) {
        return 1;               //     already loaded
    }

    //       load the dll 
    hashdll = LoadLibraryA("HashDLL.dll");
    if (hashdll == NULL) {
        printf("err: couldn't load HashDLL.dll. make sure it's in the same folder as the program!!!! \n");
        return 0;
    }

    p = GetProcAddress(hashdll, "hash");
    if (p == NULL) {
        printf("err: couldn't load HashDLL.dll. make sure it's in the same folder as the program!!!! \"C\".\n");
        FreeLibrary(hashdll);
        hashdll = NULL;
        return 0;
    }

    //       cast the symbol 2 func pointer type
    hashfunc = (hashfxn)p;
    return 1;
}

//         imp the same functio
unsigned char* hash(char* cmd, unsigned char* nodehash) {
    if (hashfunc == NULL) {
        int okiedokie;
        okiedokie = loadHashDLL();
        if (okiedokie == 0) {
            static unsigned char fail[5];
            int i;
            for (i = 0; i < 5; i++) {
                fail[i] = 0;
            }
            //   print and exit
            printf("err: Hash function is unavailable. exiting....\n");
            exit(1);
            return fail;
        }
    }
    return hashfunc(cmd, nodehash);
}

//      call this b4 exit 2 unload
void unloadHashDLL(void) {
    if (hashdll != NULL) {
        FreeLibrary(hashdll);
        hashdll = NULL;
        hashfunc = NULL;
    }
}
