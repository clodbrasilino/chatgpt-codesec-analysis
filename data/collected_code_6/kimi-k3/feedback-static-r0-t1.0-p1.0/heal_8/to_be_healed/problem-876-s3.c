#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

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
    char buffer[128];
    char *endptr;
    unsigned long long temp;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if ((len == 0) || (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n')) {
        return -1;
    }

    errno = 0;
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