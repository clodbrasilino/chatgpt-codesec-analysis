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

static int read_decimal(uintmax_t positive_limit,
                        bool allow_negative,
                        uintmax_t negative_limit,
                        bool *negative,
                        uintmax_t *magnitude)
{
    int ch;
    bool is_negative = false;
    bool saw_digit = false;
    bool invalid = false;
    uintmax_t result = 0;
    uintmax_t limit;

    if (negative == NULL || magnitude == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch));

    if (ch == '+' || ch == '-') {
        is_negative = ch == '-';

        if (is_negative && !allow_negative) {
            invalid = true;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            saw_digit = true;

            if (result > limit / 10 ||
                (result == limit / 10 && digit > limit % 10)) {
                invalid = true;
            } else {
                result = result * 10 + digit;
            }
        } else {
            invalid = true;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    if (!saw_digit || invalid) {
        return -1;
    }

    *negative = is_negative;
    *magnitude = result;
    return 0;
}

static int read_size_value(size_t *value)
{
    bool negative;
    uintmax_t magnitude;

    if (value == NULL ||
        read_decimal((uintmax_t)SIZE_MAX,
                     false,
                     (uintmax_t)SIZE_MAX,
                     &negative,
                     &magnitude) != 0) {
        return -1;
    }

    *value = (size_t)magnitude;
    return 0;
}

static int read_int64_value(int64_t *value)
{
    bool negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit = (uintmax_t)INT64_MAX + 1;

    if (value == NULL ||
        read_decimal((uintmax_t)INT64_MAX,
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

    if (read_size_value(&count) != 0) {
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
        if (read_int64_value(&tuples[i].key) != 0 ||
            read_int64_value(&tuples[i].value) != 0) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64_value(&order[i]) != 0) {
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