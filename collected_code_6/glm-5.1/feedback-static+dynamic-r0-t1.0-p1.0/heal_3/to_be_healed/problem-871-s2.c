#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

int areRotations(const char *str1, const char *str2) {
    size_t len1, len2;
    char *concat;
    int result;
    size_t concat_len;

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

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    concat_len = 2 * len1;
    concat = (char *)malloc(concat_len + 1);
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
    concat[concat_len] = '\0';

    result = strstr(concat, str2) != NULL;

    free(concat);

    return result;
}

int main(void) {
    const char *s1 = "abcd";
    const char *s2 = "cdab";
    const char *s3 = "acbd";

    if (areRotations(s1, s2)) {
        printf("%s and %s are rotations of each other.\n", s1, s2);
    } else {
        printf("%s and %s are not rotations of each other.\n", s1, s2);
    }

    if (areRotations(s1, s3)) {
        printf("%s and %s are rotations of each other.\n", s1, s3);
    } else {
        printf("%s and %s are not rotations of each other.\n", s1, s3);
    }

    return 0;
}