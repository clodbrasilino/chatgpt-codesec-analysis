#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1024 };

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t half;
    uint64_t other;
    uint64_t product;

    if (result == NULL) {
        return 0;
    }

    if ((n & UINT64_C(1)) == 0) {
        half = n / UINT64_C(2);
        other = n + UINT64_C(1);
    } else {
        half = n / UINT64_C(2) + UINT64_C(1);
        other = n;
    }

    if (half != 0 && other > UINT64_MAX / half) {
        return 0;
    }

    product = half * other;

    if (product != 0 && product > UINT64_MAX / product) {
        return 0;
    }

    product *= product;

    if (product > UINT64_MAX / UINT64_C(8)) {
        return 0;
    }

    *result = UINT64_C(8) * product;
    return 1;
}

static int discard_remainder(FILE *stream)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return 1;
            }
            ++i;
        }
    }

    return !ferror(stream);
}

static int read_input(char **buffer)
{
    char *data;
    size_t length;
    int complete;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;

    data = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (data == NULL) {
        return 0;
    }

    if (fgets(data, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        free(data);
        return 0;
    }

    length = 0;
    complete = 0;

    while (data[length] != '\0') {
        if (data[length] == '\n') {
            data[length] = '\0';
            complete = 1;
            break;
        }
        ++length;
    }

    if (!complete) {
        if (length > (size_t)MAX_INPUT_LENGTH) {
            discard_remainder(stdin);
            free(data);
            return 0;
        }

        if (!feof(stdin)) {
            char probe[2];

            if (fgets(probe, sizeof probe, stdin) == NULL) {
                if (ferror(stdin)) {
                    free(data);
                    return 0;
                }
            } else if (probe[0] != '\n') {
                if (!discard_remainder(stdin)) {
                    free(data);
                    return 0;
                }

                free(data);
                return 0;
            }
        }
    }

    *buffer = data;
    return 1;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    uintmax_t value;
    uint64_t sum;

    if (!read_input(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!cube_sum_even((uint64_t)value, &sum)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}