#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t sum;

    if (result == NULL) {
        return 0;
    }

    a = n;
    /* Possible weaknesses found:
     *  Assignment 'b=n+1U', assigned value is greater than 0
     */
    b = n + 1U;

    /* Possible weaknesses found:
     *  Condition 'b==0U' is always false
     *  Condition 'b==0U' is always false [knownConditionTrueFalse]
     */
    if (b == 0U) {
        return 0;
    }

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if ((a != 0U) && (b > UINT64_MAX / a)) {
        return 0;
    }

    sum = a * b;

    if ((sum != 0U) && (sum > UINT64_MAX / sum)) {
        return 0;
    }

    *result = (sum * sum) - sum;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;
    int scan_result;

    printf("Enter n: ");
    scan_result = scanf("%" SCNu64, &n);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fprintf(stderr, "Result is outside the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", difference);
    return EXIT_SUCCESS;
}