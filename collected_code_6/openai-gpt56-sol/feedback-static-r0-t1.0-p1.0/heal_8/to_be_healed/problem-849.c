#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        char *result;

        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        if (capacity - length > (size_t)INT_MAX) {
            free(buffer);
            return 0;
        }

        result = fgets(buffer + length, (int)(capacity - length), stdin);

        if (result == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }

            buffer[length] = '\0';
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity > SIZE_MAX / 2) {
            free(buffer);
            return 0;
        }

        size_t new_capacity = capacity * 2;
        char *new_buffer = realloc(buffer, new_capacity);

        if (new_buffer == NULL) {
            free(buffer);
            return 0;
        }

        buffer = new_buffer;
        capacity = new_capacity;
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end;
    uintmax_t value;
    uint64_t sum;

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value < 2) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_prime_divisors((uint64_t)value, &sum)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}