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
        char *str = malloc(strlen(test_strings[i]) + 1);
        if (str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        strcpy(str, test_strings[i]);
        printf("Before: \"%s\"\n", str);
        remove_multiple_spaces(str);
        printf("After:  \"%s\"\n\n", str);

        free(str);
        str = NULL;
    }

    return EXIT_SUCCESS;
}