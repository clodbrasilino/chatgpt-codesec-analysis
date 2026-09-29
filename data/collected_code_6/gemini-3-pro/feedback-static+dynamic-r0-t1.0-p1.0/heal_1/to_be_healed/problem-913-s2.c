#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_number_at_end(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    return isdigit((unsigned char)str[len - 1]) ? 1 : 0;
}

int main(void) {
    const char *test_strings[] = {
        "helloWorld123",
        "helloWorld",
        "test1",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            printf("String: '%s', Has number at end: %d\n", test_strings[i], has_number_at_end(test_strings[i]));
        } else {
            printf("String: NULL, Has number at end: %d\n", has_number_at_end(test_strings[i]));
        }
    }

    return 0;
}