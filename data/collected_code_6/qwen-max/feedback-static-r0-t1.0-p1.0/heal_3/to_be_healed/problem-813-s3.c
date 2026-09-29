#include <stdio.h>
#include <string.h>

size_t string_length(const char *str, size_t max_len) {
    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        i++;
    }
    return i;
}

int main() {
    const char *test_string = "Hello, World!";
    /* Possible weaknesses found:
     *  Variable 'max_len' is assigned a value that is never used. [unreadVariable]
     */
    size_t max_len = 100;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Length: %zu\n", string_length(test_string, strlen(test_string) + 1));
    return 0;
}