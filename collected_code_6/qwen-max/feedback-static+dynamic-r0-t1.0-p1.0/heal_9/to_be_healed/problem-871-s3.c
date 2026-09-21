#include <stdio.h>
#include <string.h>

int are_rotations(const char *str1, const char *str2) {
    size_t len1 = strnlen(str1, 51);
    size_t len2 = strnlen(str2, 51);

    if (len1 != len2) {
        return 0;
    }

    if (len1 > 50) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[2 * len1 + 1];
    snprintf(temp, sizeof(temp), "%.*s%.*s", (int)len1, str1, (int)len1, str1);
    temp[2 * len1] = '\0';

    return strstr(temp, str2) != NULL;
}

int main() {
    const char str1[] = "waterbottle";
    const char str2[] = "erbottlewat";

    if (are_rotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}