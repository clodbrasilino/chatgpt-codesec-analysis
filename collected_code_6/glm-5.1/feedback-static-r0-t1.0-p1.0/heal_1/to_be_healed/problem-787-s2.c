#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 4) {
        return false;
    }

    for (size_t i = 0; i <= len - 4; i++) {
        if (str[i] == 'a' && str[i + 1] == 'b' && str[i + 2] == 'b' && str[i + 3] == 'b') {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *test1 = "abbb";
    const char *test2 = "aabbb";
    const char *test3 = "abb";
    const char *test4 = "acbbb";
    const char *test5 = NULL;

    printf("%d\n", match_pattern(test1));
    printf("%d\n", match_pattern(test2));
    printf("%d\n", match_pattern(test3));
    printf("%d\n", match_pattern(test4));
    printf("%d\n", match_pattern(test5));

    return 0;
}