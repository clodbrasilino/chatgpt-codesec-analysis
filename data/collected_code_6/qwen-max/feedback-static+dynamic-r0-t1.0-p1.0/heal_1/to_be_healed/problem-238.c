#include <stdio.h>
#include <string.h>

long countNonEmptySubstrings(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    long n = strlen(s);
    return (n * (n + 1)) / 2;
}

int main() {
    const char *str = "test";
    long count = countNonEmptySubstrings(str);
    printf("Number of non-empty substrings: %ld\n", count);
    return 0;
}