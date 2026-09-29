#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <ctype.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return -1;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0 && a > UINT64_MAX / a) {
        return -1;
    }

    a *= a;

    if (a > UINT64_MAX / UINT64_C(2)) {
        return -1;
    }

    *result = UINT64_C(2) * a;
    return 0;
}

static int read_number(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    uintmax_t parsed;

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

        if (length == SIZE_MAX - 1) {
            free(line);
            return -1;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return -1;
                }
                new_capacity = capacity * 2;
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
        return -2;
    }

    if (length == 0 && ch == EOF) {
        free(line);
        return -3;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(line, length + 1);

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
        return -3;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -3;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 0;
}

int main(void)
{
    uint64_t input;
    uint64_t result;
    int status;

    status = read_number(&input);
    if (status != 0) {
        if (status == -2) {
            fputs("Failed to read input.\n", stderr);
        } else if (status == -1) {
            fputs("Unable to store input.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (cube_sum_even(input, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}