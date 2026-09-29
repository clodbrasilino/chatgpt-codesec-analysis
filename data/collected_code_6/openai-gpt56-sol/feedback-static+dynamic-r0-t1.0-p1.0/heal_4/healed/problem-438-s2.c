#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;

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

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int is_space_character(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (is_space_character(ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !is_space_character(ch)) {
        if (length == capacity - 1) {
            char *larger;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            larger = realloc(buffer, new_capacity);
            if (larger == NULL) {
                free(buffer);
                return -1;
            }

            buffer = larger;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int add_product(uint64_t *total, uint64_t a, uint64_t b)
{
    uint64_t product;

    if (total == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return -1;
    }

    product = a * b;

    if (*total > UINT64_MAX - product) {
        return -1;
    }

    *total += product;
    return 0;
}

static size_t lower_bound_tuple(const Tuple *tuples, size_t count,
                                const Tuple *key)
{
    size_t first = 0;
    size_t length = count;

    while (length != 0) {
        size_t half = length / 2;
        size_t middle = first + half;

        if (compare_tuples(&tuples[middle], key) < 0) {
            first = middle + 1;
            length -= half + 1;
        } else {
            length = half;
        }
    }

    return first;
}

static size_t upper_bound_tuple(const Tuple *tuples, size_t count,
                                const Tuple *key)
{
    size_t first = 0;
    size_t length = count;

    while (length != 0) {
        size_t half = length / 2;
        size_t middle = first + half;

        if (compare_tuples(key, &tuples[middle]) < 0) {
            length = half;
        } else {
            first = middle + 1;
            length -= half + 1;
        }
    }

    return first;
}

static int count_bidirectional_pairs(Tuple *tuples, size_t count,
                                     uint64_t *result)
{
    uint64_t total = 0;
    size_t i = 0;

    if (result == NULL || (tuples == NULL && count != 0) ||
        count > UINT64_MAX) {
        return -1;
    }

    if (count > 1) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }

    while (i < count) {
        size_t j = i + 1;
        uint64_t occurrences;

        while (j < count &&
               tuples[j].first == tuples[i].first &&
               tuples[j].second == tuples[i].second) {
            ++j;
        }

        occurrences = (uint64_t)(j - i);

        if (tuples[i].first == tuples[i].second) {
            if (occurrences > 1) {
                uint64_t a = occurrences;
                uint64_t b = occurrences - 1;

                if ((a & UINT64_C(1)) == 0) {
                    a /= 2;
                } else {
                    b /= 2;
                }

                if (add_product(&total, a, b) != 0) {
                    return -1;
                }
            }
        } else if (tuples[i].first < tuples[i].second) {
            Tuple reverse;
            size_t start;
            size_t end;

            reverse.first = tuples[i].second;
            reverse.second = tuples[i].first;

            start = lower_bound_tuple(tuples, count, &reverse);
            end = upper_bound_tuple(tuples, count, &reverse);

            if (start < end) {
                uint64_t reverse_occurrences = (uint64_t)(end - start);

                if (add_product(&total, occurrences,
                                reverse_occurrences) != 0) {
                    return -1;
                }
            }
        }

        i = j;
    }

    *result = total;
    return 0;
}

int main(void)
{
    char *token = NULL;
    size_t count;
    Tuple *tuples = NULL;
    uint64_t result;

    if (read_token(&token) != 0 || parse_size(token, &count) != 0) {
        free(token);
        fputs("Invalid tuple count.\n", stderr);
        return EXIT_FAILURE;
    }

    free(token);
    token = NULL;

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_token(&token) != 0 ||
            parse_int64(token, &tuples[i].first) != 0) {
            free(token);
            free(tuples);
            fputs("Invalid tuple input.\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;

        if (read_token(&token) != 0 ||
            parse_int64(token, &tuples[i].second) != 0) {
            free(token);
            free(tuples);
            fputs("Invalid tuple input.\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;
    }

    if (count_bidirectional_pairs(tuples, count, &result) != 0) {
        free(tuples);
        fputs("Unable to count pairs safely.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(tuples);
        fputs("Output failed.\n", stderr);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}