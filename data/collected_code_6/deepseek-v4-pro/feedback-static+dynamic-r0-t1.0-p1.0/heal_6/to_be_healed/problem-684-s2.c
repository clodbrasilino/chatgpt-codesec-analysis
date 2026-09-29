#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long count_occurrences(const char *str, char ch, long n) {
    if (str == NULL || n <= 0) {
        return 0;
    }

    size_t len = strnlen(str, 256);
    if (len == 0 || len >= 256) {
        return 0;
    }

    long full_repeats = n / (long)len;
    size_t remainder = (size_t)(n % (long)len);
    long count = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            count++;
        }
    }

    long total = count * full_repeats;

    for (size_t i = 0; i < remainder; i++) {
        if (str[i] == ch) {
            total++;
        }
    }

    return total;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[512] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[257] = {0};
    char ch = '\0';
    long n = 0;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    } else {
        input[sizeof(input) - 1] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder sscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    int scan_result = sscanf(input, "%256s %c %ld", str, &ch, &n);
    if (scan_result != 3) {
        return 1;
    }

    if (str[0] == '\0') {
        return 1;
    }

    long result = count_occurrences(str, ch, n);
    printf("%ld\n", result);

    return 0;
}