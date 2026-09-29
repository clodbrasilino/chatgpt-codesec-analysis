#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return 0;
    }
    for (size_t i = 0; i < max_len; ++i) {
        if (str[i] == '\0') {
            return i;
        }
    }
    return max_len;
}

int main() {
    const char *test_string = "Hello, world!";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = count_characters(test_string, strlen(test_string));
    printf("Total characters: %zu\n", length);
    return 0;
}