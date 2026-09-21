#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int areRotations(const char *str1, const char *str2) {
    size_t len1 = strnlen(str1, 1024);
    size_t len2 = strnlen(str2, 1024);

    if (len1 != len2 || len1 == 0 || len2 == 0) {
        return false;
    }

    char temp[2 * len1 + 1];
    snprintf(temp, sizeof(temp), "%s%s", str1, str1);

    return strstr(temp, str2) != NULL;
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