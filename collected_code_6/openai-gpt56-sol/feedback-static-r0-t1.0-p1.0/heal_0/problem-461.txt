#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

static size_t count_uppercase(const char *str)
{
    size_t count = 0U;

    if (str == NULL) {
        return 0U;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str) != 0) {
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
            return 1;
        }
        return 0;
    }

    printf("%zu\n", count_uppercase(input));
    return 0;
}