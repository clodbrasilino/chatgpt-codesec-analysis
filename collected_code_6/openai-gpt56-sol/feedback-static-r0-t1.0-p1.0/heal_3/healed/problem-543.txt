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

static int discard_remaining_line(FILE *stream)
{
    int ch;

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ch;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
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

    capacity = 128U;
    input = malloc(capacity);
    if (input == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length + 1U >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                fputs("Input too long.\n", stderr);
                goto cleanup;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                discard_remaining_line(stdin);
                fputs("Memory allocation failed.\n", stderr);
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (ch == EOF && length == 0U) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    input[length] = '\0';

    if (sscanf(input, " %" SCNd64 " %" SCNd64 " %c",
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