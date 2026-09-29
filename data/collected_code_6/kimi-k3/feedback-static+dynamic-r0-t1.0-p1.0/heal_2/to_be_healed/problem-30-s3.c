#include <stdio.h>
#include <string.h>
#include <stddef.h>

int countSubstrings(const char *str, size_t len) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *str = "abcab";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    int result = countSubstrings(str, len);

    if (result >= 0) {
        printf("Count of substrings starting and ending with same characters: %d\n", result);
    } else {
        printf("Invalid input string.\n");
    }

    return 0;
}