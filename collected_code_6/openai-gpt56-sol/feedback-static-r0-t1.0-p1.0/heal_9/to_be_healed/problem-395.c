#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return 0;
        }
        ++frequencies[data[i]];
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1U) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 1024 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_CAPACITY];
    unsigned char result = 0;
    size_t length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
                return 1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= sizeof input) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != EOF && character != '\n');

            if (character == EOF && ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }

            return 1;
        }

        input[length++] = (unsigned char)character;
    }

    if (find_first_non_repeated(input, length, &result)) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            fputs("Output error\n", stderr);
            return 1;
        }
    } else if (puts("No non-repeated character found") == EOF) {
        fputs("Output error\n", stderr);
        return 1;
    }

    return 0;
}