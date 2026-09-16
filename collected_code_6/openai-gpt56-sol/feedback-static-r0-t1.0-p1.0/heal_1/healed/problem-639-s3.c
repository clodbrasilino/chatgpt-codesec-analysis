#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

size_t sum_filtered_name_lengths(const char *const names[], size_t count)
{
    size_t total = 0;

    if (names == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (names[i] == NULL || names[i][0] == '\0') {
            continue;
        }

        if (!islower((unsigned char)names[i][0])) {
            const size_t length = strlen(names[i]);

            if (length > SIZE_MAX - total) {
                return SIZE_MAX;
            }

            total += length;
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
        "Eve"
    };
    const size_t count = sizeof names / sizeof names[0];
    const size_t total = sum_filtered_name_lengths(names, count);

    if (total == SIZE_MAX) {
        fputs("Length sum overflow\n", stderr);
        return 1;
    }

    if (printf("%zu\n", total) < 0) {
        return 1;
    }

    return 0;
}