#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_prime_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 0;

    if (sum == NULL || number < 2) {
        return 0;
    }

    if (number % 2 == 0) {
        result = 2;
        do {
            number /= 2;
        } while (number % 2 == 0);
    }

    for (uint64_t divisor = 3;
         divisor <= number / divisor;
         divisor += 2) {
        if (number % divisor == 0) {
            if (UINT64_MAX - result < divisor) {
                return 0;
            }

            result += divisor;

            do {
                number /= divisor;
            } while (number % divisor == 0);
        }
    }

    if (number > 1) {
        if (UINT64_MAX - result < number) {
            return 0;
        }

        result += number;
    }

    *sum = result;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    uintmax_t value;
    uint64_t sum;
    int ch;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        goto cleanup;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            goto cleanup;
        }

        new_input = realloc(input, capacity + 1);
        if (new_input == NULL) {
            goto cleanup;
        }

        input = new_input;
        capacity++;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0' || value < 2 ||
        !sum_prime_divisors((uint64_t)value, &sum)) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}