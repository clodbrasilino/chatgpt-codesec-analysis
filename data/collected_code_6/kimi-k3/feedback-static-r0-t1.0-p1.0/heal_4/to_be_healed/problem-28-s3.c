#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

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

static int parse_uint64(const char *str, uint64_t *value)
{
    char *endptr;
    unsigned long long temp;

    if (str == NULL || *str == '\0') {
        return 0;
    }

    errno = 0;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'strtoull'
     *  implicit declaration of function 'strtoull'; did you mean 'strtoumax'? [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strtoull' with type 'unsigned long long (const char *, char **, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    temp = strtoull(str, &endptr, 10);

    if (errno != 0 || endptr == str || temp > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)temp;
    return 1;
}

int main(void)
{
    uint64_t n, k, result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *ptr;
    int valid = 0;

    printf("Enter n and k: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    ptr = input;
    
    while (*ptr == ' ' || *ptr == '\t') {
        ptr++;
    }

    if (parse_uint64(ptr, &n)) {
        while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '\n') {
            ptr++;
        }
        while (*ptr == ' ' || *ptr == '\t') {
            ptr++;
        }
        if (parse_uint64(ptr, &k)) {
            valid = 1;
        }
    }

    if (!valid) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = binomial_coefficient(n, k);
    printf("C(%" PRIu64 ", %" PRIu64 ") = %" PRIu64 "\n", n, k, result);

    return 0;
}