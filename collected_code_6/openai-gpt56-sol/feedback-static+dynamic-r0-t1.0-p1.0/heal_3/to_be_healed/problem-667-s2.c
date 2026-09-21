#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(int character)
{
    character = tolower((unsigned char)character);

    return character == 'a' ||
           character == 'e' ||
           character == 'i' ||
           character == 'o' ||
           character == 'u';
}

size_t count_vowels(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (is_vowel((unsigned char)*string)) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    size_t count = 0;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
        printf("%zu\n", count);
        return EXIT_SUCCESS;
    }

    count = count_vowels(buffer);

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}