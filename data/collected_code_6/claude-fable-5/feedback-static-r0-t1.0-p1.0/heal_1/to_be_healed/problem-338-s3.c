#include <stdio.h>
#include <string.h>
#include <limits.h>

long long countSubstrings(const char *str)
{
    long long counts[UCHAR_MAX + 1] = {0};
    long long result = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

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
    char buffer[1024];
    long long result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = countSubstrings(buffer);

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}