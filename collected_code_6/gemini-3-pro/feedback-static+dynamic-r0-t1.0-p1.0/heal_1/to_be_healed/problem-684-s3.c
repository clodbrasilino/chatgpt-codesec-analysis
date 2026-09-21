#include <stdio.h>
#include <string.h>

long long count_occurrences(const char *s, char c, long long n);

long long count_occurrences(const char *s, char c, long long n) {
    if (s == NULL || n <= 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    if (len == 0) {
        return 0;
    }

    long long count_per_string = 0;
    long long count_remainder = 0;
    size_t remainder = (size_t)(n % len);

    for (size_t i = 0; i < len; i++) {
        if (s[i] == c) {
            count_per_string++;
            if (i < remainder) {
                count_remainder++;
            }
        }
    }

    long long full_reps = n / len;
    return (full_reps * count_per_string) + count_remainder;
}

int main(void) {
    const char *test_str = "aba";
    char target = 'a';
    long long n = 10;

    long long result = count_occurrences(test_str, target, n);
    printf("%lld\n", result);

    return 0;
}