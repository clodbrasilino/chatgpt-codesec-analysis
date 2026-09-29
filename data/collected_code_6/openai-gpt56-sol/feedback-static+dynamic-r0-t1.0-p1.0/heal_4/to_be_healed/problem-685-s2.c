#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t number)
{
    uint64_t divisor;

    if (number < 2U) {
        return 0;
    }

    if (number == 2U) {
        return 1;
    }

    if (number % 2U == 0U) {
        return 0;
    }

    for (divisor = 3U; divisor <= number / divisor; divisor += 2U) {
        if (number % divisor == 0U) {
            return 0;
        }
    }

    return 1;
}

static int sum_primes(uint64_t limit, uint64_t *sum)
{
    uint64_t number;
    uint64_t total = 0U;

    if (sum == NULL) {
        return -1;
    }

    for (number = 2U; number <= limit; ++number) {
        if (is_prime(number)) {
            if (number > UINT64_MAX - total) {
                return -1;
            }
            total += number;
        }

        if (number == UINT64_MAX) {
            break;
        }
    }

    *sum = total;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1U) {
            free(line);
            return -1;
        }

        if (length + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    return -1;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return -1;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        return -1;
    }

    if (length == 0U && ch == EOF) {
        free(line);
        return -1;
    }

    if (length + 1U > capacity) {
        char *resized = realloc(line, length + 1U);

        if (resized == NULL) {
            free(line);
            return -1;
        }

        line = resized;
    }

    line[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || parsed > UINT64_MAX) {
        free(line);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 0;
}

int main(void)
{
    uint64_t limit;
    uint64_t sum;

    if (read_uint64(&limit) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_primes(limit, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}