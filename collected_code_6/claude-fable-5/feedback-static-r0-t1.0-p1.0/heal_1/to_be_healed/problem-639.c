#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

size_t sum_name_lengths(const char *const *names, size_t count)
{
    size_t total = 0;
    size_t i;

    if (names == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (names[i] == NULL) {
            continue;
        }
        if (names[i][0] == '\0') {
            continue;
        }
        if (islower((unsigned char)names[i][0])) {
            continue;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total += strlen(names[i]);
    }

    return total;
}

int main(void)
{
    const char *const names[] = { "Alice", "bob", "Charlie", "dave", "Eve" };
    size_t count = sizeof(names) / sizeof(names[0]);
    size_t result;

    result = sum_name_lengths(names, count);

    if (printf("Total length: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}