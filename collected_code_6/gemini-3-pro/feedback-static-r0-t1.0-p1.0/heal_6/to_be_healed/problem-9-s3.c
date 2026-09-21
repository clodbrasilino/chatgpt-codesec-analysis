#include <stdio.h>
#include <string.h>

int findMinimumRotations(const char* str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    if (len == 0) {
        return 0;
    }

    for (size_t i = 1; i <= len; i++) {
        int match = 1;
        for (size_t j = 0; j < len; j++) {
            if (str[(i + j) % len] != str[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return (int)i;
        }
    }

    return (int)len;
}

int main(void) {
    const char* str1 = "abc";
    int result1 = findMinimumRotations(str1);
    printf("%d\n", result1);

    const char* str2 = "aaaa";
    int result2 = findMinimumRotations(str2);
    printf("%d\n", result2);

    const char* str3 = "abab";
    int result3 = findMinimumRotations(str3);
    printf("%d\n", result3);

    return 0;
}