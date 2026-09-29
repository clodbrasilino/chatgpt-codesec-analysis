#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

size_t sum_valid_name_lengths(char **names, size_t count) {
    size_t total_length = 0;

    if (names == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; i++) {
        if (names[i] == NULL) {
            continue;
        }

        if (names[i][0] != '\0' && !islower((unsigned char)names[i][0])) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(names[i]);
        }
    }

    return total_length;
}

int main(void) {
    char *names[] = {
        "Alice",
        "bob",
        "Charlie",
        "david",
        "Eve",
        NULL,
        ""
    };
    
    size_t count = sizeof(names) / sizeof(names[0]);

    size_t result = sum_valid_name_lengths(names, count);

    printf("Total length: %zu\n", result);

    return 0;
}