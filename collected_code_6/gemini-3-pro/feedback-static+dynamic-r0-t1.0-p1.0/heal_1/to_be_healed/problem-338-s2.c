#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                if (count < __INT_MAX__) {
                    count++;
                } else {
                    return count;
                }
            }
        }
    }

    return count;
}

int main(void) {
    const char *test_str = "aba";
    int result = count_substrings(test_str);
    printf("%d\n", result);

    const char *test_str2 = "abcab";
    result = count_substrings(test_str2);
    printf("%d\n", result);

    return 0;
}