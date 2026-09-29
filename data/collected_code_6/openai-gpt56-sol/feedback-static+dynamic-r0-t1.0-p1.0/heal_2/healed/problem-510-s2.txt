#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= capacity) {
            while ((ch = getchar()) != EOF && !isspace((unsigned char)ch)) {
            }
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 1;
}

static int read_uintmax(uintmax_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-' || buffer[0] == '+') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !read_uintmax(&parsed) || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_u64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !read_uintmax(&parsed) || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static uint64_t saturating_add(uint64_t a, uint64_t b)
{
    return UINT64_MAX - a < b ? UINT64_MAX : a + b;
}

static uint64_t saturating_mul2(uint64_t value)
{
    return value > UINT64_MAX / 2 ? UINT64_MAX : value * 2;
}

static uint64_t count_subsequences(const uint64_t *array, size_t length,
                                   uint64_t k)
{
    uint64_t *products;
    uint64_t count = 0;
    size_t used = 1;

    if (array == NULL || length == 0 || k == 0) {
        return 0;
    }

    if (length == SIZE_MAX ||
        length + 1 > SIZE_MAX / sizeof(*products)) {
        return UINT64_MAX;
    }

    products = malloc((length + 1) * sizeof(*products));
    if (products == NULL) {
        return UINT64_MAX;
    }

    products[0] = 1;

    for (size_t index = 0; index < length; ++index) {
        uint64_t value = array[index];

        if (value == 0) {
            count = saturating_add(saturating_mul2(count), 1);
            continue;
        }

        if (value >= k) {
            continue;
        }

        size_t new_count = 0;

        for (size_t position = 0; position < used; ++position) {
            if (products[position] <= (k - 1) / value) {
                products[new_count++] = products[position] * value;
            }
        }

        if (new_count > UINT64_MAX ||
            count > UINT64_MAX - (uint64_t)new_count) {
            free(products);
            return UINT64_MAX;
        }

        count += (uint64_t)new_count;

        if (new_count != 0) {
            if (new_count > length + 1 - used) {
                free(products);
                return UINT64_MAX;
            }

            memmove(products + new_count, products,
                    used * sizeof(*products));
            used += new_count;
        }
    }

    free(products);
    return count;
}

int main(void)
{
    size_t length;
    uint64_t k;
    uint64_t *array = NULL;
    uint64_t result;

    if (!read_size(&length) || !read_u64(&k)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0; index < length; ++index) {
        if (!read_u64(&array[index])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    result = count_subsequences(array, length, k);
    free(array);

    if (result == UINT64_MAX) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}