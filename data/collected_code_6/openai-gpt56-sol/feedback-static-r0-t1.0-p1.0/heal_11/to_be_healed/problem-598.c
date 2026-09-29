#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_space_without_newline(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\f' || ch == '\v';
}

static bool read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (line == NULL) {
        return false;
    }

    *line = malloc(capacity);
    if (*line == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(*line);
                *line = NULL;
                return false;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(*line);
            *line = NULL;
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(*line);
                *line = NULL;
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(*line, new_capacity);

            if (resized == NULL) {
                free(*line);
                *line = NULL;
                return false;
            }

            *line = resized;
            capacity = new_capacity;
        }

        (*line)[length++] = (char)(unsigned char)ch;
    }

    (*line)[length] = '\0';
    return true;
}

static bool is_armstrong(unsigned long long number)
{
    unsigned long long temp = number;
    unsigned long long sum = 0;
    unsigned int digits = 0;

    do {
        ++digits;
        temp /= 10;
    } while (temp != 0);

    temp = number;

    do {
        unsigned long long digit = temp % 10;
        unsigned long long power = 1;

        for (unsigned int i = 0; i < digits; ++i) {
            if (digit != 0 && power > ULLONG_MAX / digit) {
                return false;
            }
            power *= digit;
        }

        if (sum > ULLONG_MAX - power) {
            return false;
        }

        sum += power;
        temp /= 10;
    } while (temp != 0);

    return sum == number;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end = NULL;
    unsigned long long number;

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

    start = input;

    while (is_space_without_newline((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        puts("Not an Armstrong number");
        free(input);
        return EXIT_SUCCESS;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (is_space_without_newline((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_armstrong(number)
             ? "Armstrong number"
             : "Not an Armstrong number");

    free(input);
    return EXIT_SUCCESS;
}