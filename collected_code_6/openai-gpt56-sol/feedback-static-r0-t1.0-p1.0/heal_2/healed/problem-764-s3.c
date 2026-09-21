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
        unsigned char ch = (unsigned char)*text++;

        if (isdigit(ch)) {
            if (!in_number) {
                ++count;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
    }

    return count;
}

int main(void)
{
    char buffer[4096];
    size_t count = 0;
    int in_number = 0;

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        const unsigned char *cursor = (const unsigned char *)buffer;

        while (*cursor != '\0') {
            if (isdigit(*cursor)) {
                if (!in_number) {
                    ++count;
                    in_number = 1;
                }
            } else {
                in_number = 0;
            }

            ++cursor;
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