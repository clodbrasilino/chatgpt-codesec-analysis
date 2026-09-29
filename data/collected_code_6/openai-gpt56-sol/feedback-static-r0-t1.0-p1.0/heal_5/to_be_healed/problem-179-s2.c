#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ULLONG_DECIMAL_DIGITS \
    ((sizeof(unsigned long long) * CHAR_BIT * 30103ULL) / 100000ULL + 1ULL)

static bool is_keith_number(unsigned long long number)
{
    unsigned long long sequence[ULLONG_DECIMAL_DIGITS];
    unsigned long long value = number;
    size_t count = 0;
    size_t index = 0;

    if (number < 10ULL) {
        return false;
    }

    do {
        if (count >= ULLONG_DECIMAL_DIGITS) {
            return false;
        }

        sequence[count++] = value % 10ULL;
        value /= 10ULL;
    } while (value != 0ULL);

    for (size_t i = 0; i < count / 2; ++i) {
        unsigned long long temporary = sequence[i];
        sequence[i] = sequence[count - i - 1];
        sequence[count - i - 1] = temporary;
    }

    for (;;) {
        unsigned long long sum = 0ULL;

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
        index = (index + 1U) % count;
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
            size_t new_capacity = capacity == 0 ? 32U : capacity * 2U;
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

    if (character == EOF && ferror(stdin)) {
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
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
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