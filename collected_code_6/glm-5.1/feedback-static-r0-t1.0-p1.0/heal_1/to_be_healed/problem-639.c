#include <stdio.h>
#include <string.h>
#include <ctype.h>

size_t sum_valid_names_length(char **names, size_t count) {
    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (names[i] != NULL && names[i][0] != '\0') {
            if (isupper((unsigned char)names[i][0])) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                total_length += strlen(names[i]);
            }
        }
    }
    return total_length;
}

int main(void) {
    char *names[] = {"Alice", "bob", "Charlie", "david", "Eve", NULL};
    size_t count = sizeof(names) / sizeof(names[0]) - 1;

    size_t result = sum_valid_names_length(names, count);
    printf("%zu\n", result);
    return 0;
}