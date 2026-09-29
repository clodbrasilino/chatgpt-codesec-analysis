#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(uintmax_t a, uintmax_t b, uintmax_t *result)
{
    uintmax_t divisor;

    if (a == 0 || b == 0 || result == NULL) {
        return -1;
    }

    divisor = gcd(a, b);

    if (a / divisor > UINTMAX_MAX / b) {
        return -1;
    }

    *result = (a / divisor) * b;
    return 0;
}

int main(void)
{
    uintmax_t a;
    uintmax_t b;
    uintmax_t result;
    int scan_result;

    errno = 0;
    scan_result = scanf("%" SCNuMAX " %" SCNuMAX, &a, &b);

    if (scan_result != 2 || errno == ERANGE || a == 0 || b == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        fprintf(stderr, "LCM cannot be represented\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}