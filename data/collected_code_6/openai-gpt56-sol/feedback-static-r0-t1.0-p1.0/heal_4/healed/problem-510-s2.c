#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

static int checked_add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || b > UINT64_MAX - a) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_mul2_add1_u64(uint64_t value, uint64_t *result)
{
    if (result == NULL || value > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
        return 0;
    }

    *result = value * UINT64_C(2) + UINT64_C(1);
    return 1;
}

static int read_token(char *buffer, size_t size)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    for (;;) {
        ch = getchar();

        if (ch == EOF) {
            return 0;
        }

        if (!isspace((unsigned char)ch)) {
            break;
        }
    }

    do {
        if (length + 1 >= size) {
            do {
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));

            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';

    return !ferror(stdin);
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '+' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || end == NULL || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '+' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || end == NULL || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int count_subsequences(const uint64_t *array, size_t length,
                              uint64_t k, uint64_t *result)
{
    uint64_t *products;
    uint64_t count = 0;
    size_t capacity;
    size_t used = 1;

    if (result == NULL || (array == NULL && length != 0)) {
        return 0;
    }

    *result = 0;

    if (length == 0 || k == 0) {
        return 1;
    }

    if (length == SIZE_MAX) {
        return 0;
    }

    capacity = length + 1;

    if (capacity > SIZE_MAX / sizeof(*products)) {
        return 0;
    }

    products = malloc(capacity * sizeof(*products));
    if (products == NULL) {
        return 0;
    }

    products[0] = UINT64_C(1);

    for (size_t index = 0; index < length; ++index) {
        const uint64_t value = array[index];

        if (value == 0) {
            if (!checked_mul2_add1_u64(count, &count)) {
                free(products);
                return 0;
            }
            continue;
        }

        if (value >= k) {
            continue;
        }

        const uint64_t limit = (k - UINT64_C(1)) / value;
        size_t new_count = 0;

        for (size_t position = 0; position < used; ++position) {
            if (products[position] <= limit) {
                if (new_count >= capacity) {
                    free(products);
                    return 0;
                }

                products[new_count++] = products[position] * value;
            }
        }

        if (new_count > UINT64_MAX ||
            !checked_add_u64(count, (uint64_t)new_count, &count)) {
            free(products);
            return 0;
        }

        if (new_count != 0) {
            if (new_count > capacity - used ||
                used > SIZE_MAX / sizeof(*products)) {
                free(products);
                return 0;
            }

            memmove(products + new_count, products,
                    used * sizeof(*products));
            used += new_count;
        }
    }

    free(products);
    *result = count;
    return 1;
}

int main(void)
{
    enum { TOKEN_SIZE = 128 };
    char token[TOKEN_SIZE];
    size_t length;
    uint64_t k;
    uint64_t *array = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (!read_token(token, sizeof(token)) ||
        !parse_size(token, &length) ||
        !read_token(token, sizeof(token)) ||
        !parse_uint64(token, &k)) {
        goto cleanup;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        goto cleanup;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            goto cleanup;
        }
    }

    for (size_t index = 0; index < length; ++index) {
        if (!read_token(token, sizeof(token)) ||
            !parse_uint64(token, &array[index])) {
            goto cleanup;
        }
    }

    if (!count_subsequences(array, length, k, &result)) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    return status;
}