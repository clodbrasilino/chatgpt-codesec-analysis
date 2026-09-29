#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return true;
    }

    char first = str[0];
    for (size_t i = 1; i < len; i++) {
        if (str[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abaa";
    const char *test3 = "";
    const char *test4 = NULL;

    printf("%d\n", are_all_chars_same(test1));
    printf("%d\n", are_all_chars_same(test2));
    printf("%d\n", are_all_chars_same(test3));
    printf("%d\n", are_all_chars_same(test4));

    return 0;
}