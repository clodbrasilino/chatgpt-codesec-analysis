#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    LDS_OK = 0,
    LDS_INVALID_ARGUMENT,
    LDS_NO_MEMORY
} LdsStatus;

typedef struct {
    FILE *stream;
    unsigned char buffer[4096];
    size_t position;
    size_t length;
} InputReader;

static int compare_uint64(const void *left, const void *right)
{
    const uint64_t a = *(const uint64_t *)left;
    const uint64_t b = *(const uint64_t *)right;

    return (a > b) - (a < b);
}

static int uint64_to_size(uint64_t value, size_t *result)
{
    size_t converted;

    if (result == NULL) {
        return -1;
    }

    converted = (size_t)value;
    if ((uint64_t)converted != value) {
        return -1;
    }

    *result = converted;
    return 0;
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
                lengths[j] < SIZE_MAX &&
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

    if (best_length > SIZE_MAX / sizeof(*result)) {
        free(sorted);
        free(lengths);
        free(parents);
        return LDS_INVALID_ARGUMENT;
    }

    result = malloc(best_length * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        free(lengths);
        free(parents);
        return LDS_NO_MEMORY;
    }

    {
        size_t current = best_index;

        for (size_t i = best_length; i > 0; --i) {
            result[i - 1] = sorted[current];

            if (i > 1) {
                current = parents[current];
            }
        }
    }

    free(sorted);
    free(lengths);
    free(parents);

    *subset = result;
    *subset_count = best_length;

    return LDS_OK;
}

static int input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return -1;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;

    return 0;
}

static int input_reader_get(InputReader *reader, unsigned char *value)
{
    if (reader == NULL || reader->stream == NULL || value == NULL) {
        return -1;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer,
                               sizeof(reader->buffer[0]),
                               sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            return ferror(reader->stream) ? -1 : 0;
        }
    }

    *value = reader->buffer[reader->position++];
    return 1;
}

static int read_uint64(InputReader *reader, uint64_t *value)
{
    unsigned char ch = 0;
    uint64_t result = 0;
    int status;
    int valid = 1;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    do {
        status = input_reader_get(reader, &ch);

        if (status <= 0) {
            return status;
        }
    } while (isspace((int)ch) != 0);

    for (;;) {
        if (isspace((int)ch) != 0) {
            break;
        }

        if (ch < (unsigned char)'0' || ch > (unsigned char)'9') {
            valid = 0;
        } else if (valid) {
            const uint64_t digit =
                (uint64_t)(ch - (unsigned char)'0');

            if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
                valid = 0;
            } else {
                result = result * UINT64_C(10) + digit;
            }
        }

        status = input_reader_get(reader, &ch);

        if (status < 0) {
            return -1;
        }

        if (status == 0) {
            break;
        }
    }

    if (!valid) {
        return -1;
    }

    *value = result;
    return 1;
}

static int write_uintmax(FILE *stream, uintmax_t value)
{
    char buffer[(sizeof(uintmax_t) * CHAR_BIT) / 3 + 3];
    size_t position = sizeof(buffer);

    if (stream == NULL) {
        return -1;
    }

    do {
        buffer[--position] = (char)('0' + value % UINTMAX_C(10));
        value /= UINTMAX_C(10);
    } while (value != 0);

    {
        const size_t length = sizeof(buffer) - position;

        if (fwrite(buffer + position, 1, length, stream) != length) {
            return -1;
        }
    }

    return 0;
}

static int print_subset(const uint64_t *subset, size_t count)
{
    if (count > 0 && subset == NULL) {
        return -1;
    }

    if (write_uintmax(stdout, (uintmax_t)count) != 0 ||
        fputc('\n', stdout) == EOF) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i > 0 && fputc(' ', stdout) == EOF) {
            return -1;
        }

        if (write_uintmax(stdout, (uintmax_t)subset[i]) != 0) {
            return -1;
        }
    }

    if (fputc('\n', stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    InputReader reader;
    uint64_t count_value;
    uint64_t *numbers = NULL;
    uint64_t *subset = NULL;
    size_t count;
    size_t subset_count = 0;
    LdsStatus status;

    if (input_reader_init(&reader, stdin) != 0) {
        fputs("Input initialization failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_uint64(&reader, &count_value) != 1 ||
        uint64_to_size(count_value, &count) != 0) {
        fputs("Invalid element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*numbers)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        numbers = malloc(count * sizeof(*numbers));

        if (numbers == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_uint64(&reader, &numbers[i]) != 1 ||
            numbers[i] == 0) {
            fputs("Invalid array element.\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    status = largest_divisible_subset(numbers,
                                      count,
                                      &subset,
                                      &subset_count);
    free(numbers);

    if (status != LDS_OK) {
        if (status == LDS_NO_MEMORY) {
            fputs("Memory allocation failed.\n", stderr);
        } else {
            fputs("Invalid argument.\n", stderr);
        }

        free(subset);
        return EXIT_FAILURE;
    }

    if (print_subset(subset, subset_count) != 0) {
        fputs("Output failed.\n", stderr);
        free(subset);
        return EXIT_FAILURE;
    }

    free(subset);
    return EXIT_SUCCESS;
}