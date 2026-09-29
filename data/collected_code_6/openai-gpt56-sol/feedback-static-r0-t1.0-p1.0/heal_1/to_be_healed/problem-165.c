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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    printf("%zu\n", count_matching_positions(string));

    return 0;
}