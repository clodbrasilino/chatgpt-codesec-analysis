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

    for (const unsigned char *p = (const unsigned char *)text; *p != '\0'; ++p) {
        if (isdigit(*p)) {
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
    size_t count = 0;
    int in_number = 0;
    unsigned char buffer[4096];
    size_t length;

    while ((length = fread(buffer, 1, sizeof buffer, stdin)) > 0) {
        for (size_t i = 0; i < length; ++i) {
            if (isdigit(buffer[i])) {
                if (!in_number) {
                    ++count;
                    in_number = 1;
                }
            } else {
                in_number = 0;
            }
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