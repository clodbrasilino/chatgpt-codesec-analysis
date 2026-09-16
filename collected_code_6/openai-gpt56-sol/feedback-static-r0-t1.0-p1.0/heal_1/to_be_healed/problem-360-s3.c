#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int carol_number(uint32_t n, uint64_t *result)
{
    uint64_t power = 1;

    if (n == 0 || result == NULL) {
        return 0;
    }

    for (uint32_t i = 0; i < n; ++i) {
        if (power > UINT64_MAX / 2) {
            return 0;
        }
        power *= 2;
    }

    /* Possible weaknesses found:
     *  Division by zero
     *  Assuming that condition 'power<1' is not redundant
     *  Either the condition 'power<1' is redundant or there is division by zero at line 22. [zerodivcond]
     */
    if (power < 1 || power - 1 > UINT64_MAX / (power - 1)) {
        return 0;
    }

    *result = (power - 1) * (power - 1) - 2;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > UINT32_MAX) {
        fprintf(stderr, "Invalid index\n");
        return EXIT_FAILURE;
    }

    if (!carol_number((uint32_t)parsed, &result)) {
        fprintf(stderr, "Carol number exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}