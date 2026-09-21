#include <stdio.h>
#include <string.h>

unsigned long long count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    unsigned long long n = strlen(str);
    return (n * (n + 1)) / 2;
}

int main(void) {
    const char *test_str = "abcdef";
    unsigned long long result = count_substrings(test_str);
    printf("%llu\n", result);
    return 0;
}