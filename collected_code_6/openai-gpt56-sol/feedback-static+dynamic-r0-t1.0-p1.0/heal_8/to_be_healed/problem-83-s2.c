#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096U

static unsigned char add_characters(const unsigned char *string, size_t length)
{
    unsigned int sum = 0U;

    for (size_t i = 0U; i < length; ++i) {
        sum = (sum + string[i]) % (UCHAR_MAX + 1U);
    }

    return (unsigned char)sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[BUFFER_SIZE];
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length >= sizeof buffer) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = getchar();
            } while (character != '\n' && character != EOF);

            if (character == EOF && ferror(stdin)) {
                perror("stdin");
            } else {
                fputs("Input too long\n", stderr);
            }

            return EXIT_FAILURE;
        }

        buffer[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("stdin");
        return EXIT_FAILURE;
    }

    unsigned char result = add_characters(buffer, length);

    if (putchar((int)result) == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    if (putchar('\n') == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}