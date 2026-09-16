#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_factor_sum(uint64_t number, uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t factor = 2;

    if (number < 2 || result == NULL) {
        return -1;
    }

    while (factor <= number / factor) {
        while (number % factor == 0) {
            if (UINT64_MAX - sum < factor) {
                return -1;
            }

            sum += factor;
            number /= factor;
        }

        factor = (factor == 2) ? 3 : factor + 2;
    }

    if (number > 1) {
        if (UINT64_MAX - sum < number) {
            return -1;
        }

        sum += number;
    }

    *result = sum;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    const char *input_string;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer greater than 1>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input_string = argv[1];
    errno = 0;
    input = strtoumax(input_string, &end, 10);

    if (errno == ERANGE ||
        end == input_string ||
        *end != '\0' ||
        input_string[0] == '-' ||
        input < UINT64_C(2) ||
        input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (minimum_factor_sum((uint64_t)input, &result) != 0) {
        fprintf(stderr, "Unable to calculate result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}