#include <stdio.h>
#include <string.h>
#include <ctype.h>

size_t sum_valid_name_lengths(const char **names, size_t count) {
    size_t total_length = 0;

    if (names == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (names[i] != NULL && names[i][0] != '\0') {
            if (!islower((unsigned char)names[i][0])) {
                total_length += strlen(names[i]);
            }
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
    size_t total = sum_valid_name_lengths(names, count);

    printf("%zu\n", total);

    return 0;
}