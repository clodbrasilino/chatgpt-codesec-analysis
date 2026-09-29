#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

static uint64_t gcd(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static int lcm(uint64_t a, uint64_t b, uint64_t *result)
{
    uint64_t common_divisor;
    uint64_t quotient;

    if ((a == 0U) || (b == 0U) || (result == NULL)) {
        return -1;
    }

    common_divisor = gcd(a, b);
    quotient = a / common_divisor;

    if ((quotient != 0U) && (b > (UINT64_MAX / quotient))) {
        return -1;
    }

    *result = quotient * b;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long long temp;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'strtoull'
     *  implicit declaration of function 'strtoull'; did you mean 'strtoumax'? [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strtoull' with type 'unsigned long long (const char *, char **, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    temp = strtoull(buffer, &endptr, 10);

    if ((errno != 0) || (endptr == buffer)) {
        return -1;
    }

    if (temp > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)temp;
    return 0;
}

int main(void)
{
    uint64_t num1;
    uint64_t num2;
    uint64_t result;
    int status;

    if (read_uint64(&num1) != 0) {
        return 1;
    }

    if (read_uint64(&num2) != 0) {
        return 1;
    }

    if ((num1 == 0U) || (num2 == 0U)) {
        return 1;
    }

    status = lcm(num1, num2, &result);
    if (status != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}