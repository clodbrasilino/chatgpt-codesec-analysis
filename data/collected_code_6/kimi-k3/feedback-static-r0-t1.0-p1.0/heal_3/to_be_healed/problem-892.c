#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_multiple_spaces(char *str)
{
    if (str == NULL) {
        return;
    }

    char *src = str;
    char *dst = str;
    int space_found = 0;

    while (*src != '\0') {
        if (*src != ' ') {
            *dst = *src;
            dst++;
            space_found = 0;
        } else {
            if (!space_found) {
                *dst = *src;
                dst++;
                space_found = 1;
            }
        }
        src++;
    }
    *dst = '\0';
}

int main(void)
{
    char *test_strings[] = {
        "Hello    World",
        "  Leading   spaces",
        "Trailing   spaces  ",
        "Multiple     spaces     everywhere",
        "No spaces",
        "    ",
        ""
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(test_strings[i]);
        
        if (len == SIZE_MAX) {
            fprintf(stderr, "String length error\n");
            return EXIT_FAILURE;
        }

        char *str = malloc(len + 1);
        if (str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str, test_strings[i], len);
        str[len] = '\0';
        
        printf("Before: \"%s\"\n", str);
        remove_multiple_spaces(str);
        printf("After:  \"%s\"\n\n", str);

        free(str);
        str = NULL;
    }

    return EXIT_SUCCESS;
}