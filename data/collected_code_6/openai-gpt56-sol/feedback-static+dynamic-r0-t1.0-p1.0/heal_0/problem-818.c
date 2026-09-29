#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t count_lowercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (islower((unsigned char)*string) != 0) {
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
            perror("Failed to read input");
            return 1;
        }
        return 0;
    }

    printf("%zu\n", count_lowercase(input));
    return 0;
}