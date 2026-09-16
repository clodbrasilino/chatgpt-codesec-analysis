#include <stdio.h>
#include <stdint.h>
#include <limits.h>

uint64_t binomial_coefficient(uint64_t n, uint64_t k)
{
    uint64_t result = 1;
    uint64_t i;

    if (k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (i = 0; i < k; ++i) {
        if (result != 0 && (n - i) > UINT64_MAX / result) {
            return 0;
        }
        result = result * (n - i) / (i + 1);
    }

    return result;
}

int main(void)
{
    uint64_t n, k, result;

    printf("Enter n and k: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     *  %llu in format string (no. 2) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu %llu", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = binomial_coefficient(n, k);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     *  %llu in format string (no. 3) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("C(%llu, %llu) = %llu\n", n, k, result);

    return 0;
}