#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_non_empty_substrings(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    return len * (len + 1) / 2;
}

int main() {
    const char *test_str = "abc";
    size_t count = count_non_empty_substrings(test_str);
    printf("Number of non-empty substrings: %zu\n", count);
    return 0;
}