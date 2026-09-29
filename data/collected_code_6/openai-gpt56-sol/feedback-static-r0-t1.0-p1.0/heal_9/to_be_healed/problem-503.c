#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096U

static int discard_remainder(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char **output)
{
    char *line;
    size_t length;
    int ch;

    if (output == NULL) {
        return -1;
    }

    *output = NULL;

    line = malloc(MAX_INPUT_LENGTH + 2U);
    if (line == NULL) {
        return -1;
    }

    if (fgets(line, (int)(MAX_INPUT_LENGTH + 2U), stdin) == NULL) {
        free(line);
        return -1;
    }

    length = strnlen(line, MAX_INPUT_LENGTH + 2U);
    if (length == MAX_INPUT_LENGTH + 2U) {
        free(line);
        return -1;
    }

    if (length > 0U && line[length - 1U] == '\n') {
        line[length - 1U] = '\0';
        *output = line;
        return 0;
    }

    if (length > MAX_INPUT_LENGTH) {
        if (discard_remainder() != 0) {
            free(line);
            return -1;
        }

        free(line);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = getchar();
    if (ch == '\n') {
        *output = line;
        return 0;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            free(line);
            return -1;
        }

        *output = line;
        return 0;
    }

    if (discard_remainder() != 0) {
        free(line);
        return -1;
    }

    free(line);
    return -1;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    uintmax_t parsed;
    int result = -1;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0U ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (size_t)parsed;
    result = 0;

cleanup:
    free(buffer);
    return result;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    intmax_t parsed;
    int result = -1;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (errno == ERANGE || end == start ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    result = 0;

cleanup:
    free(buffer);
    return result;
}

static int add_consecutive(const int64_t *numbers, size_t count, int64_t *sum)
{
    int64_t total = 0;

    if (numbers == NULL || sum == NULL || count == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if ((numbers[i] > 0 && total > INT64_MAX - numbers[i]) ||
            (numbers[i] < 0 && total < INT64_MIN - numbers[i])) {
            return -1;
        }

        total += numbers[i];
    }

    *sum = total;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *numbers;
    int64_t sum;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof *numbers) {
        fputs("Invalid list size.\n", stderr);
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof *numbers);
    if (numbers == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_int64(&numbers[i]) != 0) {
            fputs("Invalid number.\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (add_consecutive(numbers, count, &sum) != 0) {
        fputs("Unable to calculate sum.\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(numbers);
        return EXIT_FAILURE;
    }

    free(numbers);
    return EXIT_SUCCESS;
}