#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool areRotations(const char *str1, const char *str2, size_t max_len) {
    size_t len1, len2;
    char *concat;
    bool result;

    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    len1 = strnlen(str1, max_len);
    len2 = strnlen(str2, max_len);

    if (len1 != len2 || len1 == 0 || len1 == max_len) {
        return false;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return false;
    }

    concat = (char *)malloc(2 * len1 + 1);
    if (concat == NULL) {
        return false;
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
    size_t max_len = 1024;

    if (areRotations(str1, str2, max_len)) {
        printf("\"%s\" and \"%s\" are rotations of each other.\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other.\n", str1, str2);
    }

    if (areRotations(str1, str3, max_len)) {
        printf("\"%s\" and \"%s\" are rotations of each other.\n", str1, str3);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other.\n", str1, str3);
    }

    return 0;
}