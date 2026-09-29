#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>

#define MAX_INPUT_SIZE 1024

long long countSubstrings(const char *str, size_t max_len)
{
    long long counts[UCHAR_MAX + 1] = {0};
    long long result = 0;
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return 0;
    }

    len = strnlen(str, max_len);

    for (i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        result += (counts[i] * (counts[i] + 1)) / 2;
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_SIZE];
    long long result;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = countSubstrings(buffer, sizeof(buffer));

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}