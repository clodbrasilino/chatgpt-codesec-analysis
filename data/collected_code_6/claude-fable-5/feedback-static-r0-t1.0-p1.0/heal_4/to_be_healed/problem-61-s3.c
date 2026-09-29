#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 1024U

long long count_substrings(const char *s, size_t max_len);

long long count_substrings(const char *s, size_t max_len)
{
    size_t n;
    size_t i;
    size_t table_size;
    long long *freq;
    long long prefix_sum;
    long long offset;
    long long count;

    if (s == NULL) {
        return -1;
    }

    n = strnlen(s, max_len);
    if (n == max_len) {
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
        prefix_sum += (long long)(s[i] - '0') - 1;
        count += freq[prefix_sum + offset];
        freq[prefix_sum + offset]++;
    }

    free(freq);
    return count;
}

static int read_line(char *buf, size_t buf_size)
{
    size_t len;

    if (buf == NULL || buf_size == 0U || buf_size > (size_t)INT32_MAX) {
        return -1;
    }

    if (fgets(buf, (int)buf_size, stdin) == NULL) {
        return -1;
    }

    buf[buf_size - 1U] = '\0';

    len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == buf_size - 1U) {
        int c;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            c = getchar();
        } while (c != '\n' && c != EOF);
        return -1;
    }

    buf[len] = '\0';
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    long long result;

    printf("Enter a digit string: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (read_line(buffer, sizeof buffer) != 0) {
        fprintf(stderr, "Error: failed to read input or input too long.\n");
        return EXIT_FAILURE;
    }

    result = count_substrings(buffer, sizeof buffer);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input or internal failure.\n");
        return EXIT_FAILURE;
    }

    printf("Number of substrings: %lld\n", result);
    return EXIT_SUCCESS;
}