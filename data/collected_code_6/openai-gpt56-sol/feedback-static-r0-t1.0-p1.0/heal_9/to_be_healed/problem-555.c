#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t sum;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    if (sum * sum < sum) {
        return 0;
    }

    *result = sum * sum - sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    size_t position = 0;
    uint64_t number = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    for (position = 0; buffer[position] != '\0'; ++position) {
        if (buffer[position] == '\n') {
            buffer[position] = '\0';
            break;
        }
    }

    if (buffer[position] == '\0' && position == sizeof buffer - 1) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return 0;
        }
    }

    position = 0;

    while (buffer[position] == ' ' || buffer[position] == '\t' ||
           buffer[position] == '\r' || buffer[position] == '\f' ||
           buffer[position] == '\v') {
        ++position;
    }

    if (buffer[position] < '0' || buffer[position] > '9') {
        return 0;
    }

    while (buffer[position] >= '0' && buffer[position] <= '9') {
        uint64_t digit = (uint64_t)(buffer[position] - '0');

        if (number > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        number = number * UINT64_C(10) + digit;
        ++position;
    }

    while (buffer[position] == ' ' || buffer[position] == '\t' ||
           buffer[position] == '\r' || buffer[position] == '\f' ||
           buffer[position] == '\v') {
        ++position;
    }

    if (buffer[position] != '\0') {
        return 0;
    }

    *value = number;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}