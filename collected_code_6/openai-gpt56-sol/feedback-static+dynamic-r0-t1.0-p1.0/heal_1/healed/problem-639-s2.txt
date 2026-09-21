#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int starts_with_lowercase(const char *name)
{
    if (name == NULL || name[0] == '\0') {
        return 0;
    }

    return islower((unsigned char)name[0]) != 0;
}

static size_t sum_filtered_name_lengths(const char *const names[],
                                        const size_t lengths[],
                                        size_t count)
{
    size_t total = 0;

    if (names == NULL || lengths == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length;

        if (names[i] == NULL || starts_with_lowercase(names[i])) {
            continue;
        }

        length = strnlen(names[i], lengths[i]);

        if (length == lengths[i]) {
            return SIZE_MAX;
        }

        if (SIZE_MAX - total < length) {
            return SIZE_MAX;
        }

        total += length;
    }

    return total;
}

int main(void)
{
    static const char name_0[] = "Alice";
    static const char name_1[] = "bob";
    static const char name_2[] = "Charlie";
    static const char name_3[] = "diana";
    static const char name_4[] = "Eve";

    const char *names[] = {
        name_0,
        name_1,
        name_2,
        name_3,
        name_4
    };

    const size_t lengths[] = {
        sizeof(name_0),
        sizeof(name_1),
        sizeof(name_2),
        sizeof(name_3),
        sizeof(name_4)
    };

    size_t total = sum_filtered_name_lengths(
        names,
        lengths,
        sizeof(names) / sizeof(names[0])
    );

    if (total == SIZE_MAX) {
        fputs("Invalid string or length sum overflow.\n", stderr);
        return 1;
    }

    if (printf("%zu\n", total) < 0) {
        return 1;
    }

    return 0;
}