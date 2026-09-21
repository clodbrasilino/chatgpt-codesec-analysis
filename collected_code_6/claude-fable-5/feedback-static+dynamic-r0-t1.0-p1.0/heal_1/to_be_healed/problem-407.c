#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void swap_chars(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

static void reverse_range(char *s, size_t lo, size_t hi)
{
    while (lo < hi) {
        swap_chars(&s[lo], &s[hi]);
        lo++;
        hi--;
    }
}

long long next_bigger(long long n)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[32];
    int len;
    int i;
    int j;
    long long result;

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

    swap_chars(&digits[i], &digits[j]);
    reverse_range(digits, (size_t)(i + 1), (size_t)(len - 1));

    result = 0;
    for (i = 0; i < len; i++) {
        int d = digits[i] - '0';
        if (result > (LLONG_MAX - d) / 10) {
            return -1;
        }
        result = result * 10 + d;
    }

    return result;
}

int main(void)
{
    long long inputs[] = { 12LL, 513LL, 2017LL, 414LL, 144LL, 9LL, 111LL, 531LL };
    size_t count = sizeof(inputs) / sizeof(inputs[0]);
    size_t k;

    for (k = 0; k < count; k++) {
        long long res = next_bigger(inputs[k]);
        if (res < 0) {
            printf("next_bigger(%lld) = no larger number possible\n", inputs[k]);
        } else {
            printf("next_bigger(%lld) = %lld\n", inputs[k], res);
        }
    }

    return EXIT_SUCCESS;
}