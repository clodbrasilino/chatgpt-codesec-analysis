#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t count_matching_positions(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (isalpha(character) &&
            (size_t)(tolower(character) - 'a') == i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    printf("%zu\n", count_matching_positions(string));

    return 0;
}