#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t key;
    int64_t value;
} Tuple;

typedef struct {
    FILE *stream;
    bool error;
} Input;

static int input_get(Input *input)
{
    int ch;

    if (input == NULL || input->stream == NULL) {
        return EOF;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(input->stream);

    if (ch == EOF) {
        input->error = ferror(input->stream) != 0;
    }

    return ch;
}

static int read_decimal(Input *input,
                        uintmax_t positive_limit,
                        bool allow_negative,
                        uintmax_t negative_limit,
                        bool *negative,
                        uintmax_t *magnitude)
{
    int ch;
    bool is_negative = false;
    uintmax_t result = 0;
    uintmax_t limit;

    if (input == NULL || input->stream == NULL ||
        negative == NULL || magnitude == NULL) {
        return -1;
    }

    do {
        ch = input_get(input);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    if (ch == '+' || ch == '-') {
        is_negative = ch == '-';

        if (is_negative && !allow_negative) {
            return -1;
        }

        ch = input_get(input);
    }

    if (ch < '0' || ch > '9') {
        return -1;
    }

    limit = is_negative ? negative_limit : positive_limit;

    for (;;) {
        uintmax_t digit = (uintmax_t)(ch - '0');

        if (result > limit / UINTMAX_C(10) ||
            (result == limit / UINTMAX_C(10) &&
             digit > limit % UINTMAX_C(10))) {
            return -1;
        }

        result = result * UINTMAX_C(10) + digit;
        ch = input_get(input);

        if (ch == EOF) {
            if (input->error) {
                return -1;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }

        if (ch < '0' || ch > '9') {
            return -1;
        }
    }

    *negative = is_negative;
    *magnitude = result;
    return 0;
}

static int read_size_value(Input *input, size_t *value)
{
    bool negative;
    uintmax_t magnitude;

    if (value == NULL ||
        read_decimal(input,
                     (uintmax_t)SIZE_MAX,
                     false,
                     UINTMAX_C(0),
                     &negative,
                     &magnitude) != 0) {
        return -1;
    }

    *value = (size_t)magnitude;
    return 0;
}

static int read_int64_value(Input *input, int64_t *value)
{
    bool negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);

    if (value == NULL ||
        read_decimal(input,
                     (uintmax_t)INT64_MAX,
                     true,
                     negative_limit,
                     &negative,
                     &magnitude) != 0) {
        return -1;
    }

    if (!negative) {
        *value = (int64_t)magnitude;
    } else if (magnitude == negative_limit) {
        *value = INT64_MIN;
    } else {
        *value = -(int64_t)magnitude;
    }

    return 0;
}

static int rearrange_tuples(const Tuple *tuples,
                            size_t tuple_count,
                            const int64_t *order,
                            size_t order_count,
                            Tuple **result)
{
    Tuple *rearranged = NULL;
    bool *used = NULL;

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
        free(used);
        free(rearranged);
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
    Input input = {stdin, false};
    size_t count;
    Tuple *tuples = NULL;
    int64_t *order = NULL;
    Tuple *rearranged = NULL;
    int status = EXIT_FAILURE;

    if (read_size_value(&input, &count) != 0) {
        goto cleanup;
    }

    if (count != 0) {
        if (count > SIZE_MAX / sizeof(*tuples) ||
            count > SIZE_MAX / sizeof(*order)) {
            goto cleanup;
        }

        tuples = malloc(count * sizeof(*tuples));
        order = malloc(count * sizeof(*order));

        if (tuples == NULL || order == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64_value(&input, &tuples[i].key) != 0 ||
            read_int64_value(&input, &tuples[i].value) != 0) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64_value(&input, &order[i]) != 0) {
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