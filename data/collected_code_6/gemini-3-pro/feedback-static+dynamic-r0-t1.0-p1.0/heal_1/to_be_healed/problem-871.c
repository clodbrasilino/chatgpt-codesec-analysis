#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);

    if (len1 != len2 || len1 == 0) {
        return false;
    }

    size_t concat_len = len1 * 2 + 1;
    char *temp = (char *)malloc(concat_len);
    if (temp == NULL) {
        return false;
    }

    snprintf(temp, concat_len, "%s%s", str1, str1);

    bool is_rotation = (strstr(temp, str2) != NULL);

    free(temp);

    return is_rotation;
}

int main(void) {
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other.\n");
    } else {
        printf("Strings are not rotations of each other.\n");
    }

    const char *str3 = "ABCD";
    const char *str4 = "ACBD";

    if (areRotations(str3, str4)) {
        printf("Strings are rotations of each other.\n");
    } else {
        printf("Strings are not rotations of each other.\n");
    }

    return 0;
}