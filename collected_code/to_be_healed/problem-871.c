#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areRotations(char* str1, char* str2) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int size1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int size2 = strlen(str2);

    if (size1 != size2) {
        return false;
    }

    /* Possible weaknesses found:
     *  Overlapping read/write in strcat() is undefined behavior [overlappingWriteFunction]
     *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused).
     */
    char* temp = strcat(str1, str1);

    if (strstr(temp, str2) != NULL) {
        return true;
    }

    return false;
}

int main() {
    char str1[] = "ABCD";
    char str2[] = "CDAB";

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other");
    }
    else {
        printf("Strings are not rotations of each other");
    }

    return 0;
}