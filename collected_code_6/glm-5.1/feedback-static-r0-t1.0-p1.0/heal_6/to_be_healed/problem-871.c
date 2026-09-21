#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_rotations(const char *s1, const char *s2) {
    size_t len1, len2;
    char *concat;
    int result;
    size_t concat_size;

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

    concat_size = len1 * 2 + 1;
    concat = (char *)malloc(concat_size);
    if (concat == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concat, s1, len1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(concat + len1, s1, len1);
    concat[len1 * 2] = '\0';

    result = (strstr(concat, s2) != NULL) ? 1 : 0;

    free(concat);

    return result;
}

int main(int argc, char *argv[]) {
    const char *str1 = "abcd";
    const char *str2 = "cdab";
    const char *str3 = "acbd";

    if (are_rotations(str1, str2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    if (are_rotations(str1, str3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}