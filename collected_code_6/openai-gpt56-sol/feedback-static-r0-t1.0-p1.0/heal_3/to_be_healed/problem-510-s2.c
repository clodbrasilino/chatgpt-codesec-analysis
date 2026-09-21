#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

static uint64_t saturating_add(uint64_t a, uint64_t b)
{
    return b > UINT64_MAX - a ? UINT64_MAX : a + b;
}

static uint64_t saturating_mul2(uint64_t value)
{
    return value > UINT64_MAX / 2 ? UINT64_MAX : value * 2;
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static uint64_t count_subsequences(const uint64_t *array,
                                   size_t length,
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

#if SIZE_MAX > UINT64_MAX
        if (new_count > UINT64_MAX) {
            free(products);
            return UINT64_MAX;
        }
#endif

        count = saturating_add(count, (uint64_t)new_count);

        if (new_count > 0) {
            if (new_count > length + 1 - used) {
                free(products);
                return UINT64_MAX;
            }

            memmove(products + new_count,
                    products,
                    used * sizeof(*products));
            used += new_count;
        }
    }

    free(products);
    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    size_t length;
    uint64_t k;
    uint64_t *array = NULL;
    uint64_t result;

    if (!read_token(token, sizeof(token)) ||
        !parse_size(token, &length) ||
        !read_token(token, sizeof(token)) ||
        !parse_uint64(token, &k)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0; index < length; ++index) {
        if (!read_token(token, sizeof(token)) ||
            !parse_uint64(token, &array[index])) {
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