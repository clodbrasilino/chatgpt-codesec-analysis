#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) || length == 0) {
            free(buffer);
            return -1;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int only_trailing_space(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text == ' ' || *text == '\t' || *text == '\r' ||
           *text == '\v' || *text == '\f') {
        ++text;
    }

    return *text == '\0';
}

static int read_size(size_t *value)
{
    char *line = NULL;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&line) != 0) {
        return -1;
    }

    if (line[0] == '-') {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || parsed > SIZE_MAX ||
        !only_trailing_space(end)) {
        free(line);
        return -1;
    }

    *value = (size_t)parsed;
    free(line);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&line) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    if (errno == ERANGE || end == line ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !only_trailing_space(end)) {
        free(line);
        return -1;
    }

    *value = (int64_t)parsed;
    free(line);
    return 0;
}

static uint64_t int64_magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static int sum_absolute_differences(int64_t *array, size_t length,
                                    uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t positive_prefix = 0;
    uint64_t negative_prefix = 0;

    if (array == NULL || result == NULL) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        uint64_t index;
        uint64_t value;
        uint64_t product;
        uint64_t difference_sum;

        if (i > UINT64_MAX) {
            return -1;
        }

        index = (uint64_t)i;
        value = int64_magnitude(array[i]);

        if (index != 0 && value > UINT64_MAX / index) {
            return -1;
        }

        product = value * index;

        if (array[i] >= 0) {
            if (product < positive_prefix) {
                return -1;
            }

            difference_sum = product - positive_prefix;

            if (difference_sum > UINT64_MAX - negative_prefix) {
                return -1;
            }

            difference_sum += negative_prefix;

            if (positive_prefix > UINT64_MAX - value) {
                return -1;
            }

            positive_prefix += value;
        } else {
            if (product > UINT64_MAX - negative_prefix) {
                return -1;
            }

            difference_sum = product + negative_prefix;

            if (difference_sum < positive_prefix) {
                return -1;
            }

            difference_sum -= positive_prefix;

            if (negative_prefix > UINT64_MAX - value) {
                return -1;
            }

            negative_prefix += value;
        }

        if (sum > UINT64_MAX - difference_sum) {
            return -1;
        }

        sum += difference_sum;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    uint64_t result;

    if (read_size(&length) != 0) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_absolute_differences(array, length, &result) != 0) {
        fputs("Result exceeds the supported range\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}