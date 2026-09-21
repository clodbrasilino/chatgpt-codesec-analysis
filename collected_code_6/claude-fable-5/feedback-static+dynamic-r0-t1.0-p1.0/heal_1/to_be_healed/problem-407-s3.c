#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

static long long next_bigger(long long n)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[32];
    int len;
    int i;
    int j;
    long long result;
    char tmp;
    char *endptr;

    if (n < 0) {
        return -1;
    }

    len = snprintf(digits, sizeof(digits), "%lld", n);
    if (len < 0 || (size_t)len >= sizeof(digits)) {
        return -1;
    }

    i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
        i--;
    }
    if (i < 0) {
        return -1;
    }

    j = len - 1;
    while (digits[j] <= digits[i]) {
        j--;
    }

    tmp = digits[i];
    digits[i] = digits[j];
    digits[j] = tmp;

    for (int a = i + 1, b = len - 1; a < b; a++, b--) {
        tmp = digits[a];
        digits[a] = digits[b];
        digits[b] = tmp;
    }

    errno = 0;
    result = strtoll(digits, &endptr, 10);
    if (errno == ERANGE || endptr == digits || *endptr != '\0') {
        return -1;
    }

    return result;
}

int main(void)
{
    long long inputs[] = {12LL, 513LL, 2017LL, 414LL, 144LL, 9LL, 111LL, 531LL};
    size_t count = sizeof(inputs) / sizeof(inputs[0]);
    size_t k;

    for (k = 0; k < count; k++) {
        long long res = next_bigger(inputs[k]);
        if (res < 0) {
            if (printf("next_bigger(%lld) = no bigger number exists\n", inputs[k]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("next_bigger(%lld) = %lld\n", inputs[k], res) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}