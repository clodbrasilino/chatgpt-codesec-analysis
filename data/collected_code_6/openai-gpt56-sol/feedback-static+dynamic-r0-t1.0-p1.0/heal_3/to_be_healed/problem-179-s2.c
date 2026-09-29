#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_keith_number(unsigned long long number)
{
    unsigned long long sequence[sizeof(number) * CHAR_BIT];
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

    for (size_t left = 0, right = count - 1; left < right; ++left, --right) {
        unsigned long long temporary = sequence[left];
        sequence[left] = sequence[right];
        sequence[right] = temporary;
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
    char *start;
    char *end;
    unsigned long long number;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
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

    if (character == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *temporary = realloc(input, new_capacity);

        if (temporary == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = temporary;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';
    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
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

    printf("%llu is %sa Keith number.\n",
           number, is_keith_number(number) ? "" : "not ");

    free(input);
    return EXIT_SUCCESS;
}