#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

size_t sum_valid_name_lengths(const char **names, size_t count) {
    if (names == NULL) {
        return 0;
    }

    size_t total_length = 0;

    for (size_t i = 0; i < count; ++i) {
        if (names[i] == NULL) {
            continue;
        }

        if (names[i][0] != '\0' && !islower((unsigned char)names[i][0])) {
            total_length += strlen(names[i]);
        }
    }

    return total_length;
}

int main(void) {
    const char *names[] = {
        "Alice",
        "bob",
        "Charlie",
        "david",
        "Eve",
        NULL,
        ""
    };

    size_t count = sizeof(names) / sizeof(names[0]);

    size_t total_length = sum_valid_name_lengths(names, count);

    printf("Total length of valid names: %zu\n", total_length);

    return 0;
}