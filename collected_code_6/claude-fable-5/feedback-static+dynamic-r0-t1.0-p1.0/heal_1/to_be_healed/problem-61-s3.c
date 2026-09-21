#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

long long count_substrings(const char *s);

long long count_substrings(const char *s)
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    n = strlen(s);
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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    long long result;

    printf("Enter a digit string: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';

    result = count_substrings(buffer);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input or internal failure.\n");
        return EXIT_FAILURE;
    }

    printf("Number of substrings: %lld\n", result);
    return EXIT_SUCCESS;
}