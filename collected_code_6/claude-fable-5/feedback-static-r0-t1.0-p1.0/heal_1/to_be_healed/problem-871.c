#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    char *temp;
    int result;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(s2);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    temp = (char *)malloc(2 * len1 + 1);
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, s1, len1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + len1, s1, len1);
    temp[2 * len1] = '\0';

    result = (strstr(temp, s2) != NULL) ? 1 : 0;

    free(temp);
    return result;
}

int main(void)
{
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";
    const char *str3 = "ACBD";
    int res;

    res = are_rotations(str1, str2);
    if (res < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("\"%s\" and \"%s\": %s\n", str1, str2,
           (res == 1) ? "rotations" : "not rotations");

    res = are_rotations(str1, str3);
    if (res < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("\"%s\" and \"%s\": %s\n", str1, str3,
           (res == 1) ? "rotations" : "not rotations");

    return EXIT_SUCCESS;
}