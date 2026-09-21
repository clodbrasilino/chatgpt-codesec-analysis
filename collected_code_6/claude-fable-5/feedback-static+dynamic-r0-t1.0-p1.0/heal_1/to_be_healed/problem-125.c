#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSubstringDiff(const char *str, size_t len);

int maxSubstringDiff(const char *str, size_t len)
{
    int maxDiff = -1;
    int current = 0;
    size_t i;

    if (str == NULL || len == 0U) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        int value;

        if (str[i] == '0') {
            value = 1;
        } else if (str[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        current += value;

        if (current > maxDiff) {
            maxDiff = current;
        }

        if (current < 0) {
            current = 0;
        }
    }

    return maxDiff;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    size_t len;
    int result;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        (void)fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }

    result = maxSubstringDiff(buffer, len);

    if (result < 0) {
        (void)printf("-1\n");
    } else {
        (void)printf("%d\n", result);
    }

    return EXIT_SUCCESS;
}