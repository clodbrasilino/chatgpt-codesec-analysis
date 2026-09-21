#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_number_at_end(const char *str) {
    if (str == NULL || !*str) return 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) --end;

    while (end > str && isdigit(*end)) --end;

    if (*(end + 1) && !isdigit(*(end + 1))) {
        while (end > str && isspace(*end)) --end;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        return (end + 1) < (str + strlen(str) - 1) && isspace(*(end + 1));
    }

    return 0;
}

int main(void) {
    const char *test_strings[] = {"hello123", "123hello", "hello 123", "hello", ""};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("'%s': %d\n", test_strings[i], is_number_at_end(test_strings[i]));
    }
    return 0;
}