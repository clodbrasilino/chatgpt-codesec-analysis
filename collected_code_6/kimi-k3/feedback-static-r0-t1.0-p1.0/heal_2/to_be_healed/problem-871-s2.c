#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int areRotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *concat;
    int result;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(str2);

    if (len1 != len2 || len1 == 0) {
        return 0;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return 0;
    }

    concat = (char *)malloc(2 * len1 + 1);
    if (concat == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concat, str1, len1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concat + len1, str1, len1);
    concat[2 * len1] = '\0';

    result = (strstr(concat, str2) != NULL);

    free(concat);
    concat = NULL;

    return result;
}

int main(void) {
    const char *str1 = "abcde";
    const char *str2 = "cdeab";
    const char *str3 = "abced";

    if (areRotations(str1, str2)) {
        printf("\"%s\" and \"%s\" are rotations of each other.\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other.\n", str1, str2);
    }

    if (areRotations(str1, str3)) {
        printf("\"%s\" and \"%s\" are rotations of each other.\n", str1, str3);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other.\n", str1, str3);
    }

    return 0;
}