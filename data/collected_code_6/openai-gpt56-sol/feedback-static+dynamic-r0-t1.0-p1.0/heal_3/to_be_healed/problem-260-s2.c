#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t value)
{
    uint64_t divisor;

    if (value < UINT64_C(2)) {
        return 0;
    }

    if ((value & UINT64_C(1)) == 0) {
        return value == UINT64_C(2);
    }

    for (divisor = UINT64_C(3);
         divisor <= value / divisor;
         divisor += UINT64_C(2)) {
        if (value % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

static int nth_newman_shanks_williams_prime(uint64_t n, uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(1);
    uint64_t count = UINT64_C(0);

    if (n == 0 || result == NULL) {
        return 0;
    }

    for (;;) {
        uint64_t next;

        if (current > (UINT64_MAX - previous) / UINT64_C(6)) {
            return 0;
        }

        next = UINT64_C(6) * current - previous;
        previous = current;
        current = next;

        if (is_prime(current)) {
            ++count;

            if (count == n) {
                *result = current;
                return 1;
            }
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    if (!nth_newman_shanks_williams_prime((uint64_t)input, &result)) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}