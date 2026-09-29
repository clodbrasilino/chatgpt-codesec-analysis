#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool all_chars_same(const char *str)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return false;
    }

    for (i = 1; i < len; i++) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *test1 = "aaaa";
    const char *test2 = "abca";
    const char *test3 = "z";
    const char *test4 = "";

    if (all_chars_same(test1)) {
        printf("\"%s\": all characters are same\n", test1);
    } else {
        printf("\"%s\": all characters are not same\n", test1);
    }

    if (all_chars_same(test2)) {
        printf("\"%s\": all characters are same\n", test2);
    } else {
        printf("\"%s\": all characters are not same\n", test2);
    }

    if (all_chars_same(test3)) {
        printf("\"%s\": all characters are same\n", test3);
    } else {
        printf("\"%s\": all characters are not same\n", test3);
    }

    if (all_chars_same(test4)) {
        printf("\"%s\": all characters are same\n", test4);
    } else {
        printf("\"%s\": all characters are not same\n", test4);
    }

    return 0;
}