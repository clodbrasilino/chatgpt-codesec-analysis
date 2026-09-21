#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef enum {
    CHECK_ERROR = -1,
    CHECK_NOT_EQUAL = 0,
    CHECK_EQUAL = 1
} CheckResult;

static int read_token(char *buffer, size_t capacity)
{
    int character;
    size_t length = 0;
    int too_long = 0;

    if (buffer == NULL || capacity == 0) {
        return -1;
    }

    do {
        character = getchar();
        if (character == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    } while (isspace((unsigned char)character));

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)character;
        } else {
            too_long = 1;
        }

        character = getchar();
    } while (character != EOF && !isspace((unsigned char)character));

    if (character == EOF && ferror(stdin)) {
        return -1;
    }

    buffer[length] = '\0';
    return too_long ? -1 : 1;
}

static int read_size_value(size_t *value)
{
    char token[128];
    char *end;
    uintmax_t parsed;
    size_t index;
    int status;

    if (value == NULL) {
        return 0;
    }

    status = read_token(token, sizeof(token));
    if (status != 1 || token[0] == '\0') {
        return 0;
    }

    for (index = 0; token[index] != '\0'; ++index) {
        if (!isdigit((unsigned char)token[index])) {
            return 0;
        }
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char token[128];
    char *end;
    intmax_t parsed;
    size_t index = 0;
    int status;

    if (value == NULL) {
        return 0;
    }

    status = read_token(token, sizeof(token));
    if (status != 1 || token[0] == '\0') {
        return 0;
    }

    if (token[index] == '+' || token[index] == '-') {
        ++index;
    }

    if (token[index] == '\0') {
        return 0;
    }

    for (; token[index] != '\0'; ++index) {
        if (!isdigit((unsigned char)token[index])) {
            return 0;
        }
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

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

static int tuples_are_equal(const Tuple *a, const Tuple *b)
{
    return a->first == b->first && a->second == b->second;
}

static CheckResult records_have_equal_occurrences(const Tuple *tuples,
                                                   size_t count)
{
    Tuple *sorted;
    size_t index;
    size_t expected_frequency = 0;

    if (count == 0) {
        return CHECK_EQUAL;
    }

    if (tuples == NULL || count > SIZE_MAX / sizeof(*sorted)) {
        return CHECK_ERROR;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return CHECK_ERROR;
    }

    for (index = 0; index < count; ++index) {
        sorted[index] = tuples[index];
    }

    qsort(sorted, count, sizeof(*sorted), compare_tuples);

    index = 0;
    while (index < count) {
        size_t end = index + 1;
        size_t frequency;

        while (end < count &&
               tuples_are_equal(&sorted[index], &sorted[end])) {
            ++end;
        }

        frequency = end - index;

        if (expected_frequency == 0) {
            expected_frequency = frequency;
        } else if (frequency != expected_frequency) {
            free(sorted);
            return CHECK_NOT_EQUAL;
        }

        index = end;
    }

    free(sorted);
    return CHECK_EQUAL;
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t count;
    size_t index;
    CheckResult result;

    if (!read_size_value(&count)) {
        fprintf(stderr, "Failed to read the tuple count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large.\n");
        return EXIT_FAILURE;
    }

    if (count > 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return EXIT_FAILURE;
        }
    }

    for (index = 0; index < count; ++index) {
        if (!read_int64_value(&tuples[index].first) ||
            !read_int64_value(&tuples[index].second)) {
            fprintf(stderr, "Failed to read tuple %zu.\n", index + 1);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    result = records_have_equal_occurrences(tuples, count);
    free(tuples);

    if (result == CHECK_ERROR) {
        fprintf(stderr, "Unable to check record occurrences.\n");
        return EXIT_FAILURE;
    }

    puts(result == CHECK_EQUAL ? "YES" : "NO");
    return EXIT_SUCCESS;
}