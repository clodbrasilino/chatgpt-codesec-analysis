#include <stdio.h>
#include <string.h>

struct Dictionary {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char key[100];
    int value;
};

int accessDictionaryElementByKeyIndex(struct Dictionary dict[], int size, char key[]) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'key[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'dict[i].key[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (strcmp(dict[i].key, key) == 0) {
            return dict[i].value;
        }
    }
    return -1; // Key not found
}