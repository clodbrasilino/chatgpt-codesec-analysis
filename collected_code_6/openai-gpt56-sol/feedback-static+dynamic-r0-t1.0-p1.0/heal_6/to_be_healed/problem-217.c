#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    uintmax_t seen = 0;

    if (result == NULL || (data == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = data[i];
        uintmax_t mask;

        /* Possible weaknesses found:
         *  'UINTMAX_WIDTH' undeclared (first use in this function); did you mean 'UINT_WIDTH'?
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'UINTMAX_WIDTH'
         */
        if (ch >= UINTMAX_WIDTH) {
            continue;
        }

        mask = UINTMAX_C(1) << ch;

        if ((seen & mask) != 0) {
            *result = ch;
            return 1;
        }

        seen |= mask;
    }

    return 0;
}

int main(void)
{
    unsigned char *data = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char repeated;
    int c;
    int found;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_data;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return EXIT_FAILURE;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length++] = (unsigned char)c;
    }

    if (ferror(stdin)) {
        free(data);
        return EXIT_FAILURE;
    }

    found = find_first_repeated_character(data, length, &repeated);
    free(data);

    if (found) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}