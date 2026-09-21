#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LEN 256

size_t sum_name_lengths(const char *const *names, size_t count)
{
    size_t total = 0;
    size_t i;
    size_t len;

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
        len = strnlen(names[i], MAX_NAME_LEN);
        if (len == MAX_NAME_LEN) {
            continue;
        }
        total += len;
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