#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_numeric_values(const char *text)
{
    size_t count = 0;
    int in_number = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isdigit((unsigned char)*text)) {
            if (!in_number) {
                ++count;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
        ++text;
    }

    return count;
}

int main(void)
{
    size_t count = 0;
    int in_number = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (isdigit((unsigned char)ch)) {
            if (!in_number) {
                ++count;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}