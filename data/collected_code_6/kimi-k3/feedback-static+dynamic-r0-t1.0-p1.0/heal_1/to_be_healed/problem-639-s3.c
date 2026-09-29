#include <stdio.h>
#include <string.h>
#include <ctype.h>

size_t sum_lengths_after_filter(const char **names, size_t count)
{
    size_t total = 0;
    size_t i;

    if (names == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (names[i] != NULL && names[i][0] != '\0') {
            if (!islower((unsigned char)names[i][0])) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                total += strlen(names[i]);
            }
        }
    }

    return total;
}

int main(void)
{
    const char *names[] = {
        "Alice",
        "bob",
        "Charlie",
        "david",
        "Eve",
        "frank"
    };
    size_t count = sizeof(names) / sizeof(names[0]);
    size_t result;

    result = sum_lengths_after_filter(names, count);

    printf("Sum of lengths: %zu\n", result);

    return 0;
}