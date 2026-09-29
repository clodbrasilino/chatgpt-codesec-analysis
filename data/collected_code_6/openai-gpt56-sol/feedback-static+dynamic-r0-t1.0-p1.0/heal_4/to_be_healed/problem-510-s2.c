#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
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

    do {
        if (length >= capacity - 1) {
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
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 1;
}

static int read_uintmax(uintmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-' || buffer[0] == '+') {
        return 0;
    }

    errno = 0;
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

static int add_count(uint64_t *count, size_t amount)
{
    if (count == NULL || amount > UINT64_MAX ||
        *count > UINT64_MAX - (uint64_t)amount) {
        return 0;
    }

    *count += (uint64_t)amount;
    return 1;
}

static int update_zero_count(uint64_t *count)
{
    if (count == NULL || *count > (UINT64_MAX - 1) / 2) {
        return 0;
    }

    *count = *count * 2 + 1;
    return 1;
}

static int count_subsequences(const uint64_t *array, size_t length,
                              uint64_t k, uint64_t *result)
{
    uint64_t *products;
    uint64_t count = 0;
    size_t used = 1;

    if (result == NULL || (array == NULL && length != 0)) {
        return 0;
    }

    if (length == 0 || k == 0) {
        *result = 0;
        return 1;
    }

    if (length > (SIZE_MAX / sizeof(*products)) - 1) {
        return 0;
    }

    products = malloc((length + 1) * sizeof(*products));
    if (products == NULL) {
        return 0;
    }

    products[0] = 1;

    for (size_t index = 0; index < length; ++index) {
        uint64_t value = array[index];
        size_t new_count = 0;

        if (value == 0) {
            if (!update_zero_count(&count)) {
                free(products);
                return 0;
            }
            continue;
        }

        if (value >= k) {
            continue;
        }

        for (size_t position = 0; position < used; ++position) {
            if (products[position] <= (k - 1) / value) {
                products[new_count++] = products[position] * value;
            }
        }

        if (!add_count(&count, new_count)) {
            free(products);
            return 0;
        }

        if (new_count != 0) {
            if (new_count > length + 1 - used ||
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

    if (!count_subsequences(array, length, k, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}