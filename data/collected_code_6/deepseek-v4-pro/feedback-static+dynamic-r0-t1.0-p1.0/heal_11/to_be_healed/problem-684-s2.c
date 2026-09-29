#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

long count_occurrences(const char *str, char ch, long n) {
    if (str == NULL || n <= 0) {
        return 0;
    }

    size_t len = strnlen(str, 256);
    if (len == 0 || len >= 256) {
        return 0;
    }

    if (n > LONG_MAX / 256) {
        n = LONG_MAX / 256;
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
    char *input = NULL;
    size_t input_size = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[257] = {0};
    char ch = '\0';
    long n = 0;

    ssize_t line_len = getline(&input, &input_size, stdin);
    if (line_len == -1) {
        free(input);
        return 1;
    }

    if (line_len > 0 && input[line_len - 1] == '\n') {
        input[line_len - 1] = '\0';
        line_len--;
    }

    if (line_len == 0) {
        free(input);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp_str[257] = {0};
    /* Possible weaknesses found:
     * Flawfinder sscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    int scan_result = sscanf(input, "%256s %c %ld", temp_str, &ch, &n);
    free(input);

    if (scan_result != 3) {
        return 1;
    }

    if (temp_str[0] == '\0') {
        return 1;
    }

    size_t temp_len = strnlen(temp_str, sizeof(temp_str) - 1);
    if (temp_len == 0 || temp_len >= sizeof(str)) {
        return 1;
    }

    if (temp_len + 1 <= sizeof(str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str, temp_str, temp_len);
        str[temp_len] = '\0';
    } else {
        return 1;
    }

    long result = count_occurrences(str, ch, n);
    printf("%ld\n", result);

    return 0;
}