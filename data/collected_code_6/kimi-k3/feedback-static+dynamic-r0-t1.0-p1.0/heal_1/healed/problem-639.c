#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

size_t sum_name_lengths(const char *names[], size_t count, size_t max_len)
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
        total += strnlen(names[i], max_len);
    }

    return total;
}

int main(void)
{
    const char *names[] = {
        "Alice",
        "bob",
        "Charlie",
        "dave",
        "Eve",
        "frank"
    };
    size_t count = sizeof(names) / sizeof(names[0]);
    size_t result;
    size_t max_len = 1024;

    result = sum_name_lengths(names, count, max_len);
    printf("Sum of lengths: %zu\n", result);

    return 0;
}