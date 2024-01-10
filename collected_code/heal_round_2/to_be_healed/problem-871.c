#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areRotations(const char* str1, const char* str2) {
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
  
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[2*size1+1];
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp, str1, size1);
    temp[size1] = '\0';
    /* Possible weaknesses found:
     *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
     */
    strncat(temp, str1, size1);
  
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