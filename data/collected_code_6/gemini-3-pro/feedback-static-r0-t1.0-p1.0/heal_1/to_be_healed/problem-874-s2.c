#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isConcatenation(const char *str) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return false;
    }

    for (size_t i = 1; i <= len / 2; ++i) {
        if (len % i == 0) {
            bool match = true;
            for (size_t j = i; j < len; ++j) {
                if (str[j] != str[j % i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    const char *test1 = "abcabc";
    const char *test2 = "ababab";
    const char *test3 = "abcd";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("%d\n", isConcatenation(test1));
    printf("%d\n", isConcatenation(test2));
    printf("%d\n", isConcatenation(test3));
    printf("%d\n", isConcatenation(test4));
    printf("%d\n", isConcatenation(test5));

    return 0;
}