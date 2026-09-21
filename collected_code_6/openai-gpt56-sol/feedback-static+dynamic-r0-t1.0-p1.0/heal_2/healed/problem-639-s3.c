#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 4096U

size_t sum_filtered_name_lengths(
    const char *const names[],
    const size_t lengths[],
    size_t count)
{
    size_t total = 0;

    if (names == NULL || lengths == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        const char *name = names[i];
        size_t length = lengths[i];

        if (name == NULL || length == 0 || length > MAX_NAME_LENGTH) {
            continue;
        }

        if (!islower((unsigned char)name[0])) {
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
    const size_t lengths[] = {
        sizeof "Alice" - 1,
        sizeof "bob" - 1,
        sizeof "Charlie" - 1,
        sizeof "david" - 1,
        sizeof "Eve" - 1
    };
    const size_t count = sizeof names / sizeof names[0];
    const size_t total = sum_filtered_name_lengths(names, lengths, count);

    if (total == SIZE_MAX) {
        if (fputs("Length sum overflow\n", stderr) == EOF) {
            return 1;
        }

        return 1;
    }

    if (printf("%zu\n", total) < 0) {
        return 1;
    }

    return 0;
}