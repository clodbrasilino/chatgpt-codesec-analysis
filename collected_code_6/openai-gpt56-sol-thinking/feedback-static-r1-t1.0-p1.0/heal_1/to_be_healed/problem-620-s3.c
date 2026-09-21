#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    LDS_OK = 0,
    LDS_INVALID_ARGUMENT,
    LDS_NO_MEMORY
} LdsStatus;

static int compare_uint64(const void *left, const void *right)
{
    const uint64_t a = *(const uint64_t *)left;
    const uint64_t b = *(const uint64_t *)right;

    return (a > b) - (a < b);
}

LdsStatus largest_divisible_subset(const uint64_t *numbers,
                                   size_t count,
                                   uint64_t **subset,
                                   size_t *subset_count)
{
    uint64_t *sorted = NULL;
    uint64_t *result = NULL;
    size_t *lengths = NULL;
    size_t *parents = NULL;
    size_t best_length = 0;
    size_t best_index = 0;

    if (subset == NULL || subset_count == NULL) {
        return LDS_INVALID_ARGUMENT;
    }

    *subset = NULL;
    *subset_count = 0;

    if (count == 0) {
        return LDS_OK;
    }

    if (numbers == NULL ||
        count > SIZE_MAX / sizeof(*sorted) ||
        count > SIZE_MAX / sizeof(*lengths) ||
        count > SIZE_MAX / sizeof(*parents)) {
        return LDS_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] == 0) {
            return LDS_INVALID_ARGUMENT;
        }
    }

    sorted = malloc(count * sizeof(*sorted));
    lengths = malloc(count * sizeof(*lengths));
    parents = malloc(count * sizeof(*parents));

    if (sorted == NULL || lengths == NULL || parents == NULL) {
        free(sorted);
        free(lengths);
        free(parents);
        return LDS_NO_MEMORY;
    }

    for (size_t i = 0; i < count; ++i) {
        sorted[i] = numbers[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_uint64);

    for (size_t i = 0; i < count; ++i) {
        lengths[i] = 1;
        parents[i] = i;

        for (size_t j = 0; j < i; ++j) {
            if (sorted[i] % sorted[j] == 0 &&
                lengths[j] + 1 > lengths[i]) {
                lengths[i] = lengths[j] + 1;
                parents[i] = j;
            }
        }

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    result = malloc(best_length * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        free(lengths);
        free(parents);
        return LDS_NO_MEMORY;
    }

    size_t current = best_index;
    for (size_t i = best_length; i > 0; --i) {
        result[i - 1] = sorted[current];
        if (i > 1) {
            current = parents[current];
        }
    }

    free(sorted);
    free(lengths);
    free(parents);

    *subset = result;
    *subset_count = best_length;
    return LDS_OK;
}

static int read_uint64(FILE *stream, uint64_t *value)
{
    int ch;
    uint64_t result = 0;
    int valid = 1;

    if (stream == NULL || value == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stream) ? -1 : 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch < '0' || ch > '9') {
            valid = 0;
        } else if (valid) {
            const uint64_t digit = (uint64_t)(ch - '0');

            if (result > (UINT64_MAX - digit) / 10) {
                valid = 0;
            } else {
                result = result * 10 + digit;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        return -1;
    }

    if (!valid) {
        return -1;
    }

    *value = result;
    return 1;
}

static int print_subset(const uint64_t *subset, size_t count)
{
    if (printf("%zu\n", count) < 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        if (printf("%s%" PRIu64, i == 0 ? "" : " ", subset[i]) < 0) {
            return -1;
        }
    }

    if (putchar('\n') == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    uint64_t count_value;
    uint64_t *numbers = NULL;
    uint64_t *subset = NULL;
    size_t count;
    size_t subset_count = 0;
    LdsStatus status;

    if (read_uint64(stdin, &count_value) != 1 ||
        count_value > SIZE_MAX) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    count = (size_t)count_value;

    if (count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Element count is too large.\n");
        return EXIT_FAILURE;
    }

    if (count > 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_uint64(stdin, &numbers[i]) != 1 || numbers[i] == 0) {
            fprintf(stderr, "Invalid array element.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    status = largest_divisible_subset(numbers, count, &subset, &subset_count);
    free(numbers);

    if (status != LDS_OK) {
        fprintf(stderr, "%s\n",
                status == LDS_NO_MEMORY
                    ? "Memory allocation failed."
                    : "Invalid argument.");
        free(subset);
        return EXIT_FAILURE;
    }

    if (print_subset(subset, subset_count) != 0) {
        fprintf(stderr, "Output failed.\n");
        free(subset);
        return EXIT_FAILURE;
    }

    free(subset);
    return EXIT_SUCCESS;
}