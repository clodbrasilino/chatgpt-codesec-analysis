#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

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

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int parse_uintmax(const char *text, uintmax_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '+' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_uintmax_value(uintmax_t *value)
{
    char *token = NULL;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    valid = parse_uintmax(token, value);
    free(token);
    return valid;
}

static int read_int64_value(int64_t *value)
{
    char *token = NULL;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    valid = parse_int64(token, value);
    free(token);
    return valid;
}

static int read_tuples(Tuple **list, size_t *count)
{
    uintmax_t input_count;
    size_t tuple_count;
    Tuple *allocated;
    size_t i;

    if (list == NULL || count == NULL) {
        return 0;
    }

    *list = NULL;
    *count = 0;

    if (!read_uintmax_value(&input_count) ||
        input_count > (uintmax_t)SIZE_MAX ||
        input_count > (uintmax_t)(SIZE_MAX / sizeof(Tuple))) {
        return 0;
    }

    tuple_count = (size_t)input_count;

    if (tuple_count == 0) {
        return 1;
    }

    allocated = malloc(tuple_count * sizeof(*allocated));
    if (allocated == NULL) {
        return 0;
    }

    for (i = 0; i < tuple_count; ++i) {
        if (!read_int64_value(&allocated[i].first) ||
            !read_int64_value(&allocated[i].second)) {
            free(allocated);
            return 0;
        }
    }

    *list = allocated;
    *count = tuple_count;
    return 1;
}

static MaximumMatch find_maximum_similar_indices(
    const Tuple *first_list,
    size_t first_count,
    const Tuple *second_list,
    size_t second_count)
{
    MaximumMatch result = {0, 0, INT64_C(0), 0};
    size_t i;
    size_t j;

    if ((first_count != 0 && first_list == NULL) ||
        (second_count != 0 && second_list == NULL)) {
        return result;
    }

    for (i = 0; i < first_count; ++i) {
        for (j = 0; j < second_count; ++j) {
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

int main(void)
{
    Tuple *first_list = NULL;
    Tuple *second_list = NULL;
    size_t first_count = 0;
    size_t second_count = 0;
    MaximumMatch result;
    int status = EXIT_FAILURE;

    if (!read_tuples(&first_list, &first_count)) {
        fputs("Invalid first list\n", stderr);
        goto cleanup;
    }

    if (!read_tuples(&second_list, &second_count)) {
        fputs("Invalid second list\n", stderr);
        goto cleanup;
    }

    result = find_maximum_similar_indices(
        first_list,
        first_count,
        second_list,
        second_count
    );

    if (result.found) {
        if (printf("%zu %zu %" PRId64 "\n",
                   result.first_index,
                   result.second_index,
                   result.value) < 0) {
            goto cleanup;
        }
    } else if (puts("No match") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second_list);
    free(first_list);
    return status;
}