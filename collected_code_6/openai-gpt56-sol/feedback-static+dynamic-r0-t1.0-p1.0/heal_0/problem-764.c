#include <ctype.h>
#include <stddef.h>
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
        if (isdigit(*p) != 0) {
            if (in_number == 0) {
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
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    printf("%zu\n", count_numeric_values(input));

    if (ferror(stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}