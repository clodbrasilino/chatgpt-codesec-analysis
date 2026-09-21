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

static int read_byte(unsigned char *byte)
{
    size_t bytes_read;

    if (byte == NULL) {
        return -1;
    }

    bytes_read = fread(byte, 1, 1, stdin);

    if (bytes_read == 1) {
        return 1;
    }

    return ferror(stdin) ? -1 : 0;
}

static bool read_token(char *buffer, size_t capacity, size_t *length)
{
    unsigned char byte;
    size_t used = 0;
    bool overflow = false;
    int result;

    if (buffer == NULL || capacity == 0 || length == NULL) {
        return false;
    }

    do {
        result = read_byte(&byte);
        if (result <= 0) {
            return false;
        }
    } while (isspace(byte));

    for (;;) {
        if (used < capacity - 1) {
            buffer[used++] = (char)byte;
        } else {
            overflow = true;
        }

        result = read_byte(&byte);

        if (result < 0) {
            return false;
        }

        if (result == 0 || isspace(byte)) {
            break;
        }
    }

    if (overflow) {
        buffer[capacity - 1] = '\0';
        return false;
    }

    buffer[used] = '\0';
    *length = used;
    return true;
}

static bool read_size_value(size_t *value)
{
    const size_t capacity = sizeof(uintmax_t) * CHAR_BIT + 3;
    char *token;
    char *end = NULL;
    uintmax_t parsed;
    size_t length;
    bool valid = false;

    if (value == NULL) {
        return false;
    }

    token = malloc(capacity);
    if (token == NULL) {
        return false;
    }

    if (!read_token(token, capacity, &length) ||
        length == 0 ||
        token[0] == '-') {
        free(token);
        return false;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno != ERANGE &&
        end == token + length &&
        parsed <= SIZE_MAX) {
        *value = (size_t)parsed;
        valid = true;
    }

    free(token);
    return valid;
}

static bool read_int64_value(int64_t *value)
{
    const size_t capacity = sizeof(uintmax_t) * CHAR_BIT + 3;
    char *token;
    char *end = NULL;
    intmax_t parsed;
    size_t length;
    bool valid = false;

    if (value == NULL) {
        return false;
    }

    token = malloc(capacity);
    if (token == NULL) {
        return false;
    }

    if (!read_token(token, capacity, &length) || length == 0) {
        free(token);
        return false;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno != ERANGE &&
        end == token + length &&
        parsed >= INT64_MIN &&
        parsed <= INT64_MAX) {
        *value = (int64_t)parsed;
        valid = true;
    }

    free(token);
    return valid;
}

static int rearrange_tuples(const Tuple *tuples, size_t tuple_count,
                            const int64_t *order, size_t order_count,
                            Tuple **result)
{
    Tuple *rearranged;
    bool *used;

    if (result == NULL ||
        tuple_count != order_count ||
        (tuple_count != 0 && (tuples == NULL || order == NULL))) {
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

    if (count != 0) {
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