#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *temp = (char *)malloc((2 * len + 1) * sizeof(char));
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, str);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(temp, str);

    int min_rotations = len;
    for (int i = 1; i <= len; i++) {
        if (strncmp(str, temp + i, len) == 0) {
            min_rotations = i;
            break;
        }
    }

    free(temp);
    return min_rotations;
}

int main(void) {
    const char *test_str = "abcabc";
    int rotations = find_min_rotations(test_str);
    
    if (rotations != -1) {
        printf("%d\n", rotations);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}