#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
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

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_token(char **token)
{
    size_t length = 0U;
    size_t capacity = 32U;
    char *buffer;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (is_space_char(ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !is_space_char(ch)) {
        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return 0;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return 0;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size_value(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    valid = errno != ERANGE &&
            end != token &&
            *end == '\0' &&
            parsed <= SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(token);
    return valid;
}

static int read_int64_value(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    valid = errno != ERANGE &&
            end != token &&
            *end == '\0' &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(token);
    return valid;
}

static int read_tuples(Tuple **list, size_t *count)
{
    size_t input_count;
    Tuple *allocated;

    if (list == NULL || count == NULL) {
        return 0;
    }

    *list = NULL;
    *count = 0U;

    if (!read_size_value(&input_count) ||
        input_count > SIZE_MAX / sizeof(Tuple)) {
        return 0;
    }

    if (input_count == 0U) {
        return 1;
    }

    allocated = calloc(input_count, sizeof(*allocated));
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

int main(void)
{
    Tuple *first_list = NULL;
    Tuple *second_list = NULL;
    size_t first_count = 0U;
    size_t second_count = 0U;
    MaximumMatch result;

    if (!read_tuples(&first_list, &first_count)) {
        fputs("Invalid first list\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_tuples(&second_list, &second_count)) {
        free(first_list);
        fputs("Invalid second list\n", stderr);
        return EXIT_FAILURE;
    }

    result = find_maximum_similar_indices(
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