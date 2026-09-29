#include <stdio.h>
#include <string.h>

size_t count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    return n * (n + 1) / 2;
}

int main(void) {
    const char *s = "abc";
    size_t count = count_substrings(s);
    printf("%zu\n", count);
    return 0;
}