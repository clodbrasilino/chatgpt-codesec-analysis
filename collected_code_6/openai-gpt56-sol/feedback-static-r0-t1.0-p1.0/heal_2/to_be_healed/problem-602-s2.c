#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(const char *string,
                                    size_t length,
                                    unsigned char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (seen[character]) {
            *result = character;
            return 1;
        }

        seen[character] = true;
    }

    return 0;
}

int main(void)
{
    bool seen[UCHAR_MAX + 1] = { false };
    bool found = false;
    /* Possible weaknesses found:
     *  Variable 'repeated' is assigned a value that is never used. [unreadVariable]
     */
    unsigned char repeated = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[4096];

    while (!found) {
        size_t count = fread(input, 1, sizeof input, stdin);

        for (size_t i = 0; i < count; ++i) {
            if (input[i] == '\n') {
                found = true;
                break;
            }

            if (seen[input[i]]) {
                repeated = input[i];

                if (printf("%c\n", repeated) < 0) {
                    return EXIT_FAILURE;
                }

                return EXIT_SUCCESS;
            }

            seen[input[i]] = true;
        }

        if (count < sizeof input) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }
    }

    if (printf("No repeated character\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}