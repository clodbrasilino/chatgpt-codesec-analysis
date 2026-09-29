#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool find_most_common_character(const char *string,
                                       unsigned char *character,
                                       size_t *count)
{
    size_t frequencies[256] = {0};
    size_t highest_count = 0;
    unsigned char most_common = 0;

    if (string == NULL || character == NULL || count == NULL ||
        string[0] == '\0') {
        return false;
    }

    for (const unsigned char *current = (const unsigned char *)string;
         *current != '\0';
         ++current) {
        ++frequencies[*current];

        if (frequencies[*current] > highest_count) {
            highest_count = frequencies[*current];
            most_common = *current;
        }
    }

    *character = most_common;
    *count = highest_count;

    return true;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    unsigned char character;
    size_t count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 1;
    }

    if (!find_most_common_character(argv[1], &character, &count)) {
        fprintf(stderr, "The string must not be empty.\n");
        return 1;
    }

    printf("Most common character: %c\n", character);
    printf("Count: %zu\n", count);

    return 0;
}