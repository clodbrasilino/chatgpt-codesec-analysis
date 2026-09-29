#include <stdio.h>
#include <string.h>

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 2) {
        return 0;
    }

    const char *a_ptr = strchr(str, 'a');
    if (a_ptr == NULL) {
        return 0;
    }

    if (str[len - 1] != 'b') {
        return 0;
    }

    if (a_ptr >= (str + len - 1)) {
        return 0;
    }

    return 1;
}

int main(void) {
    const char *test_strings[] = {
        "axxxb",
        "baxb",
        "ab",
        "a",
        "b",
        "axxxbx",
        "zb",
        NULL
    };

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        int result = match_pattern(test_strings[i]);
        if (test_strings[i] != NULL) {
            printf("\"%s\": %d\n", test_strings[i], result);
        } else {
            printf("NULL: %d\n", result);
        }
    }

    return 0;
}