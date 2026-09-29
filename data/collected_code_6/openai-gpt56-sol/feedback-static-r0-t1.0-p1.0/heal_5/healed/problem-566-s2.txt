#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_digits(uintmax_t number, uintmax_t *result)
{
    uintmax_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        sum += number % UINTMAX_C(10);
        number /= UINTMAX_C(10);
    } while (number != 0);

    *result = sum;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *start;
    char *end;
    uintmax_t number;
    uintmax_t sum;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if ((ch == EOF && ferror(stdin)) || length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *resized;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, capacity + 1);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity++;
    }

    input[length] = '\0';
    start = input;

    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == '-' || *start == '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (sum_digits(number, &sum) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}