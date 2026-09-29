#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_three_lowest_positive(const int64_t *numbers,
                                     size_t count,
                                     int64_t *sum)
{
    if ((numbers == NULL && count != 0) || sum == NULL) {
        return -1;
    }

    int64_t lowest[3] = { INT64_MAX, INT64_MAX, INT64_MAX };
    size_t positives = 0;

    for (size_t i = 0; i < count; ++i) {
        const int64_t value = numbers[i];

        if (value <= 0) {
            continue;
        }

        if (positives < 3) {
            ++positives;
        }

        if (value < lowest[0]) {
            lowest[2] = lowest[1];
            lowest[1] = lowest[0];
            lowest[0] = value;
        } else if (value < lowest[1]) {
            lowest[2] = lowest[1];
            lowest[1] = value;
        } else if (value < lowest[2]) {
            lowest[2] = value;
        }
    }

    if (positives < 3) {
        return 1;
    }

    if (lowest[0] > INT64_MAX - lowest[1]) {
        return 2;
    }

    const int64_t partial = lowest[0] + lowest[1];

    if (partial > INT64_MAX - lowest[2]) {
        return 2;
    }

    *sum = partial + lowest[2];
    return 0;
}

static int read_token(char *buffer, size_t size)
{
    int c;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                c = fgetc(stdin);
            } while (c != EOF && !isspace((unsigned char)c));
            return -1;
        }

        buffer[length++] = (char)c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    } while (c != EOF && !isspace((unsigned char)c));

    buffer[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    size_t count;

    if (read_token(token, sizeof token) != 1 ||
        parse_size(token, &count) != 0 ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *numbers = NULL;

    if (count != 0) {
        numbers = malloc(count * sizeof *numbers);
        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_token(token, sizeof token) != 1 ||
            parse_int64(token, &numbers[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int64_t sum;
    const int result = sum_three_lowest_positive(numbers, count, &sum);

    free(numbers);

    if (result == 1) {
        fputs("Fewer than three positive numbers\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 2) {
        fputs("Sum overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (result != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}