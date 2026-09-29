#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 1024U

long long count_substrings(const char *s, size_t max_len);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 6, got -1
  *  test case 0 failed: expected 6, got -1
  *  test case 2 failed: expected 12, got -1
  */

long long count_substrings(const char *s, size_t max_len)
{
    size_t n;
    size_t i;
    size_t table_size;
    long long *freq;
    long long prefix_sum;
    long long offset;
    long long count;

    if (s == NULL || max_len == 0U) {
        return -1;
    }

    n = strnlen(s, max_len);
    if (n >= max_len) {
        return -1;
    }

    if (n == 0U) {
        return 0;
    }

    for (i = 0U; i < n; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return -1;
        }
    }

    if (n > ((SIZE_MAX - 1U) / 10U)) {
        return -1;
    }

    table_size = (10U * n) + 1U;

    if (table_size > (SIZE_MAX / sizeof *freq)) {
        return -1;
    }

    freq = calloc(table_size, sizeof *freq);
    if (freq == NULL) {
        return -1;
    }

    prefix_sum = 0;
    offset = (long long)n;
    count = 0;
    freq[offset] = 1;

    for (i = 0U; i < n; i++) {
        long long idx;

        prefix_sum += (long long)(s[i] - '0') - 1;
        idx = prefix_sum + offset;

        if (idx < 0 || (size_t)idx >= table_size) {
            free(freq);
            return -1;
        }

        count += freq[idx];
        freq[idx]++;
    }

    free(freq);
    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    long long result;

    if (fgets(buffer, (int)sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof buffer - 1U] = '\0';
    buffer[strcspn(buffer, "\r\n")] = '\0';

    result = count_substrings(buffer, sizeof buffer);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input or internal failure.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}