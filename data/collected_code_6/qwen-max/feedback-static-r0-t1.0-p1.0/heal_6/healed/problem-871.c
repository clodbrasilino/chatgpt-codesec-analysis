#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int areRotations(const char *str1, const char *str2) {
    size_t len1 = strnlen(str1, INT_MAX);
    size_t len2 = strnlen(str2, INT_MAX);

    if (len1 != len2 || len1 == INT_MAX || len2 == INT_MAX) {
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