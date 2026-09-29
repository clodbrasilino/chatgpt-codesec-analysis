#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int read_line(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    size_t i = 0;

    while (buffer[i] != '\0' && buffer[i] != '\n') {
        ++i;
    }

    if (buffer[i] == '\n') {
        buffer[i] = '\0';
        return 0;
    }

    if (buffer[i] == '\0' && feof(stdin)) {
        return 0;
    }

    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return -1;
}

static int parse_uintmax(const char *text, uintmax_t *value)
{
    if (text == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    char *end;
    uintmax_t parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int parse_intmax(const char *text, intmax_t *value)
{
    if (text == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0') {
        return -1;
    }

    errno = 0;
    char *end;
    intmax_t parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int largest_adjacent_product(const int32_t *values,
                                    size_t count,
                                    int64_t *result)
{
    if (values == NULL || result == NULL || count < 2) {
        return -1;
    }

    int64_t largest = (int64_t)values[0] * (int64_t)values[1];

    for (size_t i = 1; i < count - 1; ++i) {
        int64_t product = (int64_t)values[i] * (int64_t)values[i + 1];

        if (product > largest) {
            largest = product;
        }
    }

    *result = largest;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[256];
    uintmax_t input_count;

    if (read_line(line, sizeof(line)) != 0 ||
        parse_uintmax(line, &input_count) != 0 ||
        input_count < 2 ||
        input_count > SIZE_MAX ||
        input_count > SIZE_MAX / sizeof(int32_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)input_count;
    int32_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        intmax_t input;

        if (read_line(line, sizeof(line)) != 0 ||
            parse_intmax(line, &input) != 0 ||
            input < INT32_MIN ||
            input > INT32_MAX) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int32_t)input;
    }

    int64_t result;

    if (largest_adjacent_product(values, count, &result) != 0) {
        fputs("Unable to calculate product\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}