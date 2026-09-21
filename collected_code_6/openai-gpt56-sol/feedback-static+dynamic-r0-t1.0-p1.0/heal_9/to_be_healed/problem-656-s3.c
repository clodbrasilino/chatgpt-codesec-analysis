#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

enum { MAX_TOKEN_LENGTH = 128 };

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_TOKEN_LENGTH + 2];
    char *buffer;
    /* Possible weaknesses found:
     *  The scope of the variable 'length' can be reduced. [variableScope]
     */
    size_t length;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            return -1;
        }

        /* Possible weaknesses found:
         *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strcspn'
         *  call to undeclared library function 'strcspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        length = strcspn(input, "\r\n");

        if (input[length] == '\0' && !feof(stdin)) {
            int ch;

            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return -1;
        }

        input[length] = '\0';

        {
            char *start = input;
            char *end;

            while (*start != '\0' && isspace((unsigned char)*start)) {
                ++start;
            }

            if (*start == '\0') {
                continue;
            }

            end = start;
            while (*end != '\0' && !isspace((unsigned char)*end)) {
                ++end;
            }

            if (*end != '\0') {
                char *rest = end;

                while (*rest != '\0' && isspace((unsigned char)*rest)) {
                    ++rest;
                }

                if (*rest != '\0') {
                    return -1;
                }

                *end = '\0';
            }

            /* Possible weaknesses found:
             *  include '<string.h>' or provide a declaration of 'strlen'
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strlen'
             */
            length = strlen(start);
            if (length == 0 || length > MAX_TOKEN_LENGTH) {
                return -1;
            }

            buffer = malloc(length + 1U);
            if (buffer == NULL) {
                return -1;
            }

            /* Possible weaknesses found:
             *  call to undeclared library function 'memcpy' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include '<string.h>' or provide a declaration of 'memcpy'
             *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'memcpy'
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer, start, length + 1U);
            *token = buffer;
            return 0;
        }
    } while (1);
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        *end != '\0' ||
        parsed == 0 ||
        parsed > SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(buffer);
    return status;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        *end != '\0' ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(buffer);
    return status;
}

static int read_array(int64_t *array, size_t length)
{
    size_t i;

    if (array == NULL || length == 0) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int minimum_absolute_difference_sum(
    int64_t *first,
    int64_t *second,
    size_t length,
    uint64_t *result)
{
    uint64_t sum = 0;
    size_t i;

    if (first == NULL || second == NULL || result == NULL || length == 0) {
        return -1;
    }

    qsort(first, length, sizeof(*first), compare_int64);
    qsort(second, length, sizeof(*second), compare_int64);

    for (i = 0; i < length; ++i) {
        uint64_t difference = absolute_difference(first[i], second[i]);

        if (difference > UINT64_MAX - sum) {
            return -1;
        }

        sum += difference;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *first = NULL;
    int64_t *second = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (read_size(&length) != 0) {
        fputs("Invalid array length\n", stderr);
        goto cleanup;
    }

    if (length > SIZE_MAX / sizeof(*first)) {
        fputs("Array length is too large\n", stderr);
        goto cleanup;
    }

    first = malloc(length * sizeof(*first));
    if (first == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    second = malloc(length * sizeof(*second));
    if (second == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    if (read_array(first, length) != 0 ||
        read_array(second, length) != 0) {
        fputs("Invalid array input\n", stderr);
        goto cleanup;
    }

    if (minimum_absolute_difference_sum(
            first, second, length, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}