#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return false;
    }

    char temp[len1 * 2 + 1];
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