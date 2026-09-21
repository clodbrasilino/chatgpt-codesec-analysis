#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_int64(int64_t a, int64_t b, int64_t *sum)
{
    if (sum == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *sum = a + b;
    return 1;
}

static size_t digit_count(int64_t value)
{
    uint64_t magnitude;
    size_t count = 1U;

    if (value < 0) {
        magnitude = (uint64_t)(-(value + 1)) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)value;
    }

    while (magnitude >= UINT64_C(10)) {
        magnitude /= UINT64_C(10);
        ++count;
    }

    return count;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *input;
    size_t capacity = 128U;
    size_t used = 0U;

    if (stream == NULL || buffer == NULL || length == NULL) {
        errno = EINVAL;
        return 0;
    }

    *buffer = NULL;
    *length = 0U;

    input = malloc(capacity);
    if (input == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream)) {
                free(input);
                return 0;
            }

            if (used == 0U) {
                free(input);
                errno = EINVAL;
                return 0;
            }

            break;
        }

        if (used >= capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                errno = EOVERFLOW;
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 0;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[used++] = (char)(unsigned char)ch;
    }

    input[used] = '\0';
    *buffer = input;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    char trailing;
    int64_t first;
    int64_t second;
    int64_t sum;
    int status = EXIT_FAILURE;

    if (fputs("Enter two integers: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;

    if (!read_line(stdin, &input, &length)) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else if (errno == ENOMEM) {
            fputs("Memory allocation failed.\n", stderr);
        } else if (errno == EOVERFLOW) {
            fputs("Input too long.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }

        goto cleanup;
    }

    if (length == 0U ||
        sscanf(input, " %" SCNd64 " %" SCNd64 " %c",
               &first, &second, &trailing) != 2) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    if (!add_int64(first, second, &sum)) {
        fputs("Integer overflow.\n", stderr);
        goto cleanup;
    }

    if (printf("Sum: %" PRId64 "\nDigits: %zu\n",
               sum, digit_count(sum)) < 0) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}