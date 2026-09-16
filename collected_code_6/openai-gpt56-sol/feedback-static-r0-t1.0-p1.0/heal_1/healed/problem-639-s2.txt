#include <ctype.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int starts_with_lowercase(const char *name)
{
    if (name == NULL || name[0] == '\0') {
        return 0;
    }

    return islower((unsigned char)name[0]) != 0;
}

static size_t sum_filtered_name_lengths(const char *const names[], size_t count)
{
    size_t total = 0;

    if (names == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length;

        if (names[i] == NULL || starts_with_lowercase(names[i])) {
            continue;
        }

        length = strlen(names[i]);

        if (SIZE_MAX - total < length) {
            return SIZE_MAX;
        }

        total += length;
    }

    return total;
}

int main(void)
{
    const char *names[] = {
        "Alice",
        "bob",
        "Charlie",
        "diana",
        "Eve"
    };

    size_t total = sum_filtered_name_lengths(
        names,
        sizeof(names) / sizeof(names[0])
    );

    if (total == SIZE_MAX) {
        fputs("Length sum overflowed.\n", stderr);
        return 1;
    }

    if (printf("%zu\n", total) < 0) {
        return 1;
    }

    return 0;
}