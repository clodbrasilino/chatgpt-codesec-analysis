#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t count_numeric_values(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isdigit((unsigned char)*str) != 0) {
            ++count;
        }
        ++str;
    }

    return count;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    printf("%zu\n", count_numeric_values(input));
    return 0;
}