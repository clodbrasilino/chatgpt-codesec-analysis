#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_non_empty_substrings(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return 0;
    }
    return len * (len + 1) / 2;
}

int main() {
    const char *test_str = "abc";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(test_str);
    size_t count = count_non_empty_substrings(test_str, len);
    printf("Number of non-empty substrings: %zu\n", count);
    return 0;
}