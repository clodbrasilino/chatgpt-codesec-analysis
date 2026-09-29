#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t count_uppercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (isupper((unsigned char)*string) != 0) {
            ++count;
        }
        ++string;
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
        input[0] = '\0';
    }

    printf("%zu\n", count_uppercase(input));
    return 0;
}