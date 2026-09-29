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
    int64_t lowest[3] = { INT64_MAX, INT64_MAX, INT64_MAX };
    size_t positives = 0;

    if ((numbers == NULL && count != 0) || sum == NULL) {
        return -1;
    }

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

static int read_token(char **token)
{
    int c;
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        c = fgetc(stdin);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
        c = fgetc(stdin);
    }

    if (c == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
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

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
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

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    char *token = NULL;
    size_t count;
    int64_t *numbers = NULL;
    int64_t sum;
    int status;

    status = read_token(&token);
    if (status != 1 || parse_size(token, &count) != 0 ||
        count > SIZE_MAX / sizeof(*numbers)) {
        free(token);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(token);
    token = NULL;

    if (count != 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        status = read_token(&token);
        if (status != 1 || parse_int64(token, &numbers[i]) != 0) {
            free(token);
            free(numbers);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;
    }

    status = read_token(&token);
    if (status != 0) {
        free(token);
        free(numbers);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = sum_three_lowest_positive(numbers, count, &sum);
    free(numbers);

    if (status == 1) {
        fputs("Fewer than three positive numbers\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 2) {
        fputs("Sum overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}