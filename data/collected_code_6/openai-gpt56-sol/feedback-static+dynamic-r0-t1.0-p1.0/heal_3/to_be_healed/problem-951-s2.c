#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || size < 2U) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1U >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[length] = '\0';
    return 1;
}

static int parse_uintmax(const char *text, uintmax_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
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
    char *end = NULL;
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

static MaximumMatch find_maximum_similar_indices(
    const Tuple *first_list,
    size_t first_count,
    const Tuple *second_list,
    size_t second_count)
{
    MaximumMatch result = {0U, 0U, INT64_C(0), 0};

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

static int read_tuples(Tuple **list, size_t *count)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    uintmax_t input_count;

    if (list == NULL || count == NULL) {
        return 0;
    }

    *list = NULL;
    *count = 0U;

    if (!read_token(token, sizeof(token)) ||
        !parse_uintmax(token, &input_count) ||
        input_count > (uintmax_t)SIZE_MAX ||
        input_count > (uintmax_t)(SIZE_MAX / sizeof(Tuple))) {
        return 0;
    }

    *count = (size_t)input_count;

    if (*count == 0U) {
        return 1;
    }

    *list = malloc(*count * sizeof(**list));
    if (*list == NULL) {
        *count = 0U;
        return 0;
    }

    for (size_t i = 0U; i < *count; ++i) {
        if (!read_token(token, sizeof(token)) ||
            !parse_int64(token, &(*list)[i].first) ||
            !read_token(token, sizeof(token)) ||
            !parse_int64(token, &(*list)[i].second)) {
            free(*list);
            *list = NULL;
            *count = 0U;
            return 0;
        }
    }

    return 1;
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
        second_count
    );

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