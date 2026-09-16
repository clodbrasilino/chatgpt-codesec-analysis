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
        size_t current_count = ++frequencies[*current];

        if (current_count > highest_count) {
            highest_count = current_count;
            most_common = *current;
        }
    }

    *character = most_common;
    *count = highest_count;

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
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

    printf("Most common character: %c\n", (int)character);
    printf("Count: %zu\n", count);

    return 0;
}