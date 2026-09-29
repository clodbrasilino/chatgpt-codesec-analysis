#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (result == NULL || (data == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = data[i];

        if (seen[ch] != 0) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1;
    }

    return 0;
}

int main(void)
{
    unsigned char *data = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char repeated = 0;
    int found;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int c = getchar();

        if (c == EOF || c == '\n') {
            break;
        }

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
    } else {
        if (puts("No repeated character") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}