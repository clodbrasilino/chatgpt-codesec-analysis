#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t length_of_last_word(const char *string)
{
    size_t length = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (isspace((unsigned char)*string)) {
            length = 0;
        } else {
            ++length;
        }
        ++string;
    }

    return length;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    printf("%zu\n", length_of_last_word(input));
    return 0;
}