#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_abundant(unsigned long long number)
{
    unsigned long long sum = 1;

    if (number < 12) {
        return false;
    }

    for (unsigned long long divisor = 2;
         divisor <= number / divisor;
         ++divisor) {
        if (number % divisor == 0) {
            unsigned long long quotient = number / divisor;

            if (sum > number - divisor) {
                return true;
            }
            sum += divisor;

            if (quotient != divisor) {
                if (sum > number - quotient) {
                    return true;
                }
                sum += quotient;
            }
        }
    }

    return sum > number;
}

static char *read_line(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return NULL;
    }

    for (;;) {
        int character = getchar();

        if (character == '\n' || character == EOF) {
            if (character == EOF && ferror(stdin)) {
                free(input);
                return NULL;
            }
            if (character == EOF && length == 0) {
                free(input);
                return NULL;
            }
            break;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return NULL;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
    char *input = read_line();

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || number == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    puts(is_abundant(number) ? "Abundant" : "Not abundant");
    return EXIT_SUCCESS;
}