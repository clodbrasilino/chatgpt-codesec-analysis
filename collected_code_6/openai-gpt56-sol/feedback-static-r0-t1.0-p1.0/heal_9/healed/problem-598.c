#include <errno.h>
#include <limits.h>
#include <stdbool.h>
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
    int ch;

    if (line == NULL) {
        return false;
    }

    *line = malloc(capacity);
    if (*line == NULL) {
        return false;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(*line);
                *line = NULL;
                return false;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(*line, new_capacity);

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

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(*line);
        *line = NULL;
        return false;
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

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

    char *start = input;

    while (is_space_without_newline((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        puts("Not an Armstrong number");
        free(input);
        return EXIT_SUCCESS;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

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