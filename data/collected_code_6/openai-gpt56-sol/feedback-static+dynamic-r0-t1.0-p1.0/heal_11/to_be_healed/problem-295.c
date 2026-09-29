#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int sum_of_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (result > UINT64_MAX - divisor) {
                return 0;
            }
            result += divisor;

            if (paired_divisor != divisor) {
                if (result > UINT64_MAX - paired_divisor) {
                    return 0;
                }
                result += paired_divisor;
            }
        }
    }

    *sum = result;
    return 1;
}

static int read_line(char **buffer)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        if (fgets(line + length, (int)(capacity - length), stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return 0;
            }
            break;
        }

        while (line[length] != '\0' && line[length] != '\n') {
            ++length;
        }

        if (line[length] == '\n') {
            line[length] = '\0';
            *buffer = line;
            return 1;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity > SIZE_MAX / 2) {
            free(line);
            return 0;
        }

        {
            size_t new_capacity = capacity * 2;
            char *new_line;

            /* Possible weaknesses found:
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'INT_MAX'
             */
            if (new_capacity > (size_t)INT_MAX) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'INT_MAX'
                 */
                new_capacity = (size_t)INT_MAX;
            }

            if (new_capacity <= capacity) {
                free(line);
                return 0;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    uintmax_t value;
    uint64_t sum;
    int status = EXIT_FAILURE;

    if (fputs("Enter a positive integer: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&input)) {
        fputs("Unable to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value == 0 ||
        value > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected input.\n", stderr);
        goto cleanup;
    }

    if (!sum_of_divisors((uint64_t)value, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
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