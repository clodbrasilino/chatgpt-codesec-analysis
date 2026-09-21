#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_minimum_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    if (n == 0) {
        return 0;
    }

    char *temp = (char *)malloc((2 * n + 1) * sizeof(char));
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

    int rotations = n;

    for (size_t i = 1; i <= n; i++) {
        if (strncmp(str, temp + i, n) == 0) {
            rotations = i;
            break;
        }
    }

    free(temp);
    return rotations;
}

int main() {
    const char *test_str1 = "geeks";
    const char *test_str2 = "aaaa";
    const char *test_str3 = "abc";

    int res1 = find_minimum_rotations(test_str1);
    if (res1 != -1) {
        printf("%d\n", res1);
    }

    int res2 = find_minimum_rotations(test_str2);
    if (res2 != -1) {
        printf("%d\n", res2);
    }

    int res3 = find_minimum_rotations(test_str3);
    if (res3 != -1) {
        printf("%d\n", res3);
    }

    return 0;
}