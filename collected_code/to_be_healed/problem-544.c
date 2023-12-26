#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flattenTuple(int* tuple, int size) {
    char* str = malloc(size * sizeof(char));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'str' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    *str = '\0';
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char num[20];
        /* Possible weaknesses found:
         *   Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or  vsnprintf. Risk is low because the source has a constant maximum length.
         *  Cannot determine that 'num[0]' is initialized [premium-bughuntingUninit]
         *  Cannot determine that 'tuple[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sprintf(num, "%d", tuple[i]);
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused).
         */
        strcat(str, num);
        if (i < size - 1) {
            /* Possible weaknesses found:
             *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused). Risk is low because the  source is a constant character.
             */
            strcat(str, ",");
        }
    }
    return str;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    char* result = flattenTuple(tuple, size);
    printf("%s\n", result);
    free(result);
    return 0;
}