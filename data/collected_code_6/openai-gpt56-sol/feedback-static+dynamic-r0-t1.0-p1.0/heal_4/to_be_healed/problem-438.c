#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }
    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int character;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            *capacity = 0;
            return -1;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)character;
        if (character == '\n') {
            break;
        }
    }

    if (character == EOF && length == 0) {
        return -1;
    }

    (*line)[length] = '\0';
    return 0;
}

static void skip_horizontal_space(char **cursor)
{
    while (**cursor == ' ' || **cursor == '\t') {
        ++*cursor;
    }
}

static int at_line_end(char *cursor)
{
    if (*cursor == '\r') {
        ++cursor;
    }

    return *cursor == '\n' || *cursor == '\0';
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    cursor = line;
    skip_horizontal_space(&cursor);

    if (*cursor == '-' || *cursor == '+') {
        goto done;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor || parsed > SIZE_MAX) {
        goto done;
    }

    cursor = end;
    skip_horizontal_space(&cursor);

    if (!at_line_end(cursor)) {
        goto done;
    }

    *value = (size_t)parsed;
    status = 0;

done:
    free(line);
    return status;
}

static int read_tuple(Tuple *tuple)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;
    int status = -1;

    if (tuple == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    cursor = line;
    skip_horizontal_space(&cursor);

    errno = 0;
    first = strtoimax(cursor, &end, 10);
    if (errno == ERANGE || end == cursor ||
        first < INT64_MIN || first > INT64_MAX) {
        goto done;
    }

    cursor = end;
    if (*cursor != ' ' && *cursor != '\t') {
        goto done;
    }
    skip_horizontal_space(&cursor);

    errno = 0;
    second = strtoimax(cursor, &end, 10);
    if (errno == ERANGE || end == cursor ||
        second < INT64_MIN || second > INT64_MAX) {
        goto done;
    }

    cursor = end;
    skip_horizontal_space(&cursor);

    if (!at_line_end(cursor)) {
        goto done;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    status = 0;

done:
    free(line);
    return status;
}

static size_t lower_bound(const Tuple *tuples, size_t count, Tuple target)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (compare_tuples(&tuples[middle], &target) < 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static size_t upper_bound(const Tuple *tuples, size_t count, Tuple target)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (compare_tuples(&tuples[middle], &target) <= 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static int checked_choose_two(uint64_t value, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL) {
        return -1;
    }

    if (value < 2) {
        *result = 0;
        return 0;
    }

    a = value;
    b = value - 1;

    if ((a & UINT64_C(1)) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (b != 0 && a > UINT64_MAX / b) {
        return -1;
    }

    *result = a * b;
    return 0;
}

static int count_bidirectional_pairs(Tuple *tuples, size_t count,
                                     uint64_t *result)
{
    uint64_t total = 0;
    size_t index = 0;

    if (result == NULL || (count != 0 && tuples == NULL)) {
        return -1;
    }

    if (sizeof(size_t) > sizeof(uint64_t) && count > UINT64_MAX) {
        return -1;
    }

    if (count > 1) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }

    while (index < count) {
        size_t next = index + 1;
        uint64_t frequency;
        uint64_t addend = 0;

        while (next < count &&
               compare_tuples(&tuples[index], &tuples[next]) == 0) {
            ++next;
        }

        frequency = (uint64_t)(next - index);

        if (tuples[index].first == tuples[index].second) {
            if (checked_choose_two(frequency, &addend) != 0) {
                return -1;
            }
        } else if (tuples[index].first < tuples[index].second) {
            Tuple reverse;
            size_t first;
            size_t last;
            uint64_t reverse_frequency;

            reverse.first = tuples[index].second;
            reverse.second = tuples[index].first;

            first = lower_bound(tuples, count, reverse);
            last = upper_bound(tuples, count, reverse);
            reverse_frequency = (uint64_t)(last - first);

            if (reverse_frequency != 0 &&
                frequency > UINT64_MAX / reverse_frequency) {
                return -1;
            }

            addend = frequency * reverse_frequency;
        }

        if (total > UINT64_MAX - addend) {
            return -1;
        }

        total += addend;
        index = next;
    }

    *result = total;
    return 0;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    uint64_t result;

    if (read_size(&count) != 0) {
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large\n");
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_tuple(&tuples[i]) != 0) {
            fprintf(stderr, "Invalid tuple input\n");
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (count_bidirectional_pairs(tuples, count, &result) != 0) {
        fprintf(stderr, "Unable to count pairs\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output failed\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}