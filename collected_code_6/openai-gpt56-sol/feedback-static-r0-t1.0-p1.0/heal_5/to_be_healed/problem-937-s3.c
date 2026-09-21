#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int most_common_character(const unsigned char *data,
                          size_t length,
                          unsigned char *character,
                          size_t *count)
{
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'UCHAR_MAX'
     */
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    unsigned char most_common = 0;

    if (data == NULL || character == NULL || count == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return -1;
        }
        ++frequencies[data[i]];
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     */
    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            most_common = (unsigned char)i;
        }
    }

    *character = most_common;
    *count = max_count;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'UCHAR_MAX'
     *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     */
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t length = 0;
    unsigned char most_common = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        if (bytes_read > SIZE_MAX - length) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        length += bytes_read;

        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                goto input_complete;
            }

            if (frequencies[buffer[i]] == SIZE_MAX) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            ++frequencies[buffer[i]];
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }
    }

input_complete:
    length = 0;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     */
    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > 0) {
            if (length > SIZE_MAX - frequencies[i]) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
            length += frequencies[i];
        }

        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            most_common = (unsigned char)i;
        }
    }

    if (length == 0) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Most common character: '%c'\nCount: %zu\n",
           (int)most_common, max_count);

    return EXIT_SUCCESS;
}