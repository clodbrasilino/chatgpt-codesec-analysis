#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_keith_number(unsigned long long number)
{
    unsigned long long sequence[ULLONG_MAX_10_EXP + 1];
    unsigned long long value = number;
    size_t count = 0;
    size_t index = 0;

    if (number < 10) {
        return false;
    }

    do {
        sequence[count++] = value % 10;
        value /= 10;
    } while (value != 0);

    for (size_t i = 0; i < count / 2; ++i) {
        unsigned long long temporary = sequence[i];
        sequence[i] = sequence[count - i - 1];
        sequence[count - i - 1] = temporary;
    }

    for (;;) {
        unsigned long long sum = 0;

        for (size_t i = 0; i < count; ++i) {
            if (sequence[i] > ULLONG_MAX - sum) {
                return false;
            }
            sum += sequence[i];
        }

        if (sum == number) {
            return true;
        }

        if (sum > number) {
            return false;
        }

        sequence[index] = sum;
        index = (index + 1) % count;
    }
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;
    char *end;
    unsigned long long number;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;
            char *temporary;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        char *temporary = realloc(input, length + 1);

        if (temporary == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = temporary;
    }

    input[length] = '\0';

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(end, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    printf("%llu is %sa Keith number.\n",
           number, is_keith_number(number) ? "" : "not ");

    return EXIT_SUCCESS;
}