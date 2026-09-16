#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

static size_t length_of_last_word(const char *str)
{
    size_t last_length = 0U;
    size_t current_length = 0U;

    if (str == NULL) {
        return 0U;
    }

    while (*str != '\0') {
        if (isspace((unsigned char)*str) != 0) {
            if (current_length > 0U) {
                last_length = current_length;
                current_length = 0U;
            }
        } else {
            ++current_length;
        }
        ++str;
    }

    return current_length > 0U ? current_length : last_length;
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

    printf("%zu\n", length_of_last_word(input));
    return 0;
}