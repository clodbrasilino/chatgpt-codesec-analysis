#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool areRotations(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    int size1 = strnlen(str1, 1000);
    int size2 = strnlen(str2, 1000);

    if (size1 != size2) {
        return false;
    }

    char* temp = (char*)malloc((2*size1+1) * sizeof(char));
    if(temp == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp, str1, size1);
    temp[size1] = '\0';
    /* Possible weaknesses found:
     *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
     */
    strncat(temp, str1, size1);
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