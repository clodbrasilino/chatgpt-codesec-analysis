#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} Tuple;

static bool read_token(FILE *stream, char *buffer, size_t capacity)
{
    int character;
    size_t length = 0;
    bool overflow = false;

    if (stream == NULL || buffer == NULL || capacity == 0) {
        return false;
    }

    do {
        character = fgetc(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return false;
    }

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)character;
        } else {
            overflow = true;
        }

        character = fgetc(stream);
    } while (character != EOF && !isspace((unsigned char)character));

    if (character == EOF && ferror(stream)) {
        return false;
    }

    buffer[length] = '\0';
    return !overflow;
}

static bool read_size(FILE *stream, size_t *value)
{
    char token[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(stream, token, sizeof(token)) ||
        token[0] == '-' || token[0] == '\0') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int(FILE *stream, int *value)
{
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(stream, token, sizeof(token))) {
        return false;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || *end != '\0' ||
        parsed < INT32_MIN || parsed > INT32_MAX) {
        return false;
    }

    *value = (int)parsed;
    return true;
}

bool rearrange_tuples(Tuple *tuples, size_t tuple_count,
                      const int *order, size_t order_count)
{
    Tuple *result;
    unsigned char *selected;
    size_t output_index = 0;

    if ((tuple_count > 0 && tuples == NULL) ||
        (order_count > 0 && order == NULL) ||
        tuple_count > SIZE_MAX / sizeof(*result)) {
        return false;
    }

    if (tuple_count == 0) {
        return true;
    }

    result = malloc(tuple_count * sizeof(*result));
    if (result == NULL) {
        return false;
    }

    selected = calloc(tuple_count, sizeof(*selected));
    if (selected == NULL) {
        free(result);
        return false;
    }

    for (size_t order_index = 0; order_index < order_count; ++order_index) {
        for (size_t tuple_index = 0; tuple_index < tuple_count; ++tuple_index) {
            if (selected[tuple_index] == 0 &&
                tuples[tuple_index].key == order[order_index]) {
                result[output_index++] = tuples[tuple_index];
                selected[tuple_index] = 1;
            }
        }
    }

    for (size_t tuple_index = 0; tuple_index < tuple_count; ++tuple_index) {
        if (selected[tuple_index] == 0) {
            result[output_index++] = tuples[tuple_index];
        }
    }

    memcpy(tuples, result, tuple_count * sizeof(*tuples));

    free(selected);
    free(result);
    return true;
}

int main(void)
{
    Tuple *tuples = NULL;
    int *order = NULL;
    size_t tuple_count;
    size_t order_count;
    int status = EXIT_FAILURE;

    if (!read_size(stdin, &tuple_count) ||
        tuple_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count.\n", stderr);
        goto cleanup;
    }

    if (tuple_count > 0) {
        tuples = malloc(tuple_count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Unable to allocate tuple storage.\n", stderr);
            goto cleanup;
        }
    }

    for (size_t index = 0; index < tuple_count; ++index) {
        if (!read_int(stdin, &tuples[index].key) ||
            !read_int(stdin, &tuples[index].value)) {
            fputs("Invalid tuple input.\n", stderr);
            goto cleanup;
        }
    }

    if (!read_size(stdin, &order_count) ||
        order_count > SIZE_MAX / sizeof(*order)) {
        fputs("Invalid order count.\n", stderr);
        goto cleanup;
    }

    if (order_count > 0) {
        order = malloc(order_count * sizeof(*order));
        if (order == NULL) {
            fputs("Unable to allocate order storage.\n", stderr);
            goto cleanup;
        }
    }

    for (size_t index = 0; index < order_count; ++index) {
        if (!read_int(stdin, &order[index])) {
            fputs("Invalid order input.\n", stderr);
            goto cleanup;
        }
    }

    if (!rearrange_tuples(tuples, tuple_count, order, order_count)) {
        fputs("Unable to rearrange tuples.\n", stderr);
        goto cleanup;
    }

    for (size_t index = 0; index < tuple_count; ++index) {
        if (printf("%s(%d, %d)",
                   index == 0 ? "" : " ",
                   tuples[index].key,
                   tuples[index].value) < 0) {
            fputs("Output error.\n", stderr);
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(order);
    free(tuples);
    return status;
}