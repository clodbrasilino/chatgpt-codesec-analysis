#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

size_t sum_name_lengths(const char *const names[], size_t count)
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
        if (isupper((unsigned char)names[i][0])) {
            total += strlen(names[i]);
        }
    }

    return total;
}

int main(void)
{
    const char *const names[] = {
        "Alice",
        "bob",
        "Charlie",
        "dave",
        "Eve"
    };
    size_t count = sizeof(names) / sizeof(names[0]);
    size_t result;

    result = sum_name_lengths(names, count);

    if (printf("Total length: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}