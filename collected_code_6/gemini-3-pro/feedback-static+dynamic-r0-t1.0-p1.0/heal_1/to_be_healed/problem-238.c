#include <stdio.h>
#include <string.h>

unsigned long long count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    const char *test_str = "hello";
    unsigned long long result = count_substrings(test_str);
    printf("%llu\n", result);

    const char *empty_str = "";
    result = count_substrings(empty_str);
    printf("%llu\n", result);

    result = count_substrings(NULL);
    printf("%llu\n", result);

    return 0;
}