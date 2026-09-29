#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool areRotations(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int size1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int size2 = strlen(str2);

    if (size1 != size2) {
        return false;
    }

    char* temp = (char*)malloc((2*size1+1) * sizeof(char));
    if(temp == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(temp, str1, size1);
    temp[size1] = '\0';
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(temp+size1, str1, size1);
    temp[2*size1] = '\0';

    bool result = (strstr(temp, str2) != NULL);

    free(temp);

    return result;
}

int main() {
    const char str1[] = "ABCD";
    const char str2[] = "CDAB";
    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}