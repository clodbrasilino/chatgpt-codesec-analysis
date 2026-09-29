#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t key;
    int64_t value;
} Tuple;

static bool read_token(char *buffer, size_t capacity, size_t *length)
{
    int ch;
    size_t used = 0;
    bool overflow = false;

    if (buffer == NULL || capacity == 0 || length == NULL) {
        return false;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return false;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (used + 1 < capacity) {
            buffer[used++] = (char)ch;
        } else {
            overflow = true;
        }

        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    if (ch == EOF && ferror(stdin)) {
        return false;
    }

    if (overflow) {
        return false;
    }

    buffer[used] = '\0';
    *length = used;
    return true;
}

static bool read_size_value(size_t *value)
{
    char token[sizeof(uintmax_t) * CHAR_BIT + 3];
    char *end = NULL;
    uintmax_t parsed;
    size_t length;

    if (value == NULL ||
        !read_token(token, sizeof(token), &length) ||
        length == 0 ||
        token[0] == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE ||
        end != token + length ||
        parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int64_value(int64_t *value)
{
    char token[sizeof(uintmax_t) * CHAR_BIT + 3];
    char *end = NULL;
    intmax_t parsed;
    size_t length;

    if (value == NULL ||
        !read_token(token, sizeof(token), &length) ||
        length == 0) {
        return false;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE ||
        end != token + length ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    return true;
}

static int rearrange_tuples(const Tuple *tuples, size_t tuple_count,
                            const int64_t *order, size_t order_count,
                            Tuple **result)
{
    Tuple *rearranged = NULL;
    bool *used = NULL;

    if (result == NULL ||
        tuple_count != order_count ||
        (tuple_count > 0 && (tuples == NULL || order == NULL))) {
        return -1;
    }

    *result = NULL;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuple_count > SIZE_MAX / sizeof(*rearranged) ||
        tuple_count > SIZE_MAX / sizeof(*used)) {
        return -1;
    }

    rearranged = malloc(tuple_count * sizeof(*rearranged));
    used = calloc(tuple_count, sizeof(*used));

    if (rearranged == NULL || used == NULL) {
        free(rearranged);
        free(used);
        return -1;
    }

    for (size_t i = 0; i < order_count; ++i) {
        bool found = false;

        for (size_t j = 0; j < tuple_count; ++j) {
            if (!used[j] && tuples[j].key == order[i]) {
                rearranged[i] = tuples[j];
                used[j] = true;
                found = true;
                break;
            }
        }

        if (!found) {
            free(used);
            free(rearranged);
            return -1;
        }
    }

    free(used);
    *result = rearranged;
    return 0;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t *order = NULL;
    Tuple *rearranged = NULL;
    int status = EXIT_FAILURE;

    if (!read_size_value(&count)) {
        return EXIT_FAILURE;
    }

    if (count > 0) {
        if (count > SIZE_MAX / sizeof(*tuples) ||
            count > SIZE_MAX / sizeof(*order)) {
            return EXIT_FAILURE;
        }

        tuples = malloc(count * sizeof(*tuples));
        order = malloc(count * sizeof(*order));

        if (tuples == NULL || order == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&tuples[i].key) ||
            !read_int64_value(&tuples[i].value)) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&order[i])) {
            goto cleanup;
        }
    }

    if (rearrange_tuples(tuples, count, order, count, &rearranged) != 0) {
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%" PRId64 ", %" PRId64 ")%c",
                   rearranged[i].key,
                   rearranged[i].value,
                   i + 1 == count ? '\n' : ' ') < 0) {
            goto cleanup;
        }
    }

    if (count == 0 && putchar('\n') == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(rearranged);
    free(order);
    free(tuples);
    return status;
}