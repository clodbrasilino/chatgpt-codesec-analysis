#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    size_t first_index;
    size_t second_index;
    int64_t value;
    int found;
} MaximumMatch;

static MaximumMatch find_maximum_similar_indices(
    const Tuple *first_list,
    size_t first_count,
    const Tuple *second_list,
    size_t second_count)
{
    MaximumMatch result = {0U, 0U, 0, 0};

    if ((first_list == NULL && first_count != 0U) ||
        (second_list == NULL && second_count != 0U)) {
        return result;
    }

    for (size_t i = 0U; i < first_count; ++i) {
        for (size_t j = 0U; j < second_count; ++j) {
            if (first_list[i].first == second_list[j].first) {
                int64_t candidate =
                    first_list[i].second > second_list[j].second
                        ? first_list[i].second
                        : second_list[j].second;

                if (!result.found || candidate > result.value) {
                    result.first_index = i;
                    result.second_index = j;
                    result.value = candidate;
                    result.found = 1;
                }
            }
        }
    }

    return result;
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || size < 2U) {
        return 0;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    do {
        if (length + 1U >= size) {
            do {
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' &&
                     ch != '\n' && ch != '\r' && ch != '\f' &&
                     ch != '\v');
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && ch != ' ' && ch != '\t' &&
             ch != '\n' && ch != '\r' && ch != '\f' && ch != '\v');

    buffer[length] = '\0';
    return 1;
}

static int read_size_value(size_t *value)
{
    char buffer[64];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-' || buffer[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char buffer[64];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_tuples(Tuple **list, size_t *count)
{
    size_t input_count;

    if (list == NULL || count == NULL) {
        return 0;
    }

    *list = NULL;
    *count = 0U;

    if (!read_size_value(&input_count) ||
        input_count > SIZE_MAX / sizeof(**list)) {
        return 0;
    }

    if (input_count == 0U) {
        return 1;
    }

    Tuple *allocated = malloc(input_count * sizeof(*allocated));
    if (allocated == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < input_count; ++i) {
        if (!read_int64_value(&allocated[i].first) ||
            !read_int64_value(&allocated[i].second)) {
            free(allocated);
            return 0;
        }
    }

    *list = allocated;
    *count = input_count;
    return 1;
}

int main(void)
{
    Tuple *first_list = NULL;
    Tuple *second_list = NULL;
    size_t first_count = 0U;
    size_t second_count = 0U;

    if (!read_tuples(&first_list, &first_count)) {
        fputs("Invalid first list\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_tuples(&second_list, &second_count)) {
        free(first_list);
        fputs("Invalid second list\n", stderr);
        return EXIT_FAILURE;
    }

    MaximumMatch result = find_maximum_similar_indices(
        first_list,
        first_count,
        second_list,
        second_count);

    if (result.found) {
        printf("%zu %zu %" PRId64 "\n",
               result.first_index,
               result.second_index,
               result.value);
    } else {
        puts("No match");
    }

    free(second_list);
    free(first_list);
    return EXIT_SUCCESS;
}