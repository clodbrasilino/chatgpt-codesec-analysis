#include <stdio.h>
#include <string.h>

long countNonEmptySubstrings(const char *s, size_t len) {
    return (len * (len + 1)) / 2;
}

int main() {
    const char *str = "test";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    long count = countNonEmptySubstrings(str, len);
    printf("Number of non-empty substrings: %ld\n", count);
    return 0;
}