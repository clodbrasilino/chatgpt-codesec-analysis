#include <stdio.h>
#include <stddef.h>

long long count_occurrences(const char *s, char c, long long n);

long long count_occurrences(const char *s, char c, long long n) {
    if (s == NULL || n <= 0) {
        return 0;
    }

    size_t len = 0;
    while (s[len] != '\0' && len < (size_t)n) {
        len++;
    }

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