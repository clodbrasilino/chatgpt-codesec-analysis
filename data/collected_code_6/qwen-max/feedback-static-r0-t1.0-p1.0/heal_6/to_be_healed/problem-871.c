#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int areRotations(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return 0;
    }

    bool isRotation = false;
    for (size_t i = 0; i < len1; ++i) {
        if (strncmp(str1 + i, str2, len1 - i) == 0 && strncmp(str1, str2 + len1 - i, i) == 0) {
            isRotation = true;
            break;
        }
    }

    return isRotation;
}

int main() {
    const char str1[] = "waterbottle";
    const char str2[] = "erbottlewat";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}