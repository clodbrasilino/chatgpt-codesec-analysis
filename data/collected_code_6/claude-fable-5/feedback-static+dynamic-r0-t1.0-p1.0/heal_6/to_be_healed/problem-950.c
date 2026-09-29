#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define ZODIAC_COUNT 12
#define MIN_YEAR 1
#define MAX_YEAR 9999
#define INPUT_BUFFER_SIZE 64

static const char *get_chinese_zodiac(int year)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static const char *const signs[ZODIAC_COUNT] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    int index;

    index = year % ZODIAC_COUNT;
    if (index < 0) {
        index += ZODIAC_COUNT;
    }
    if (index < 0 || index >= ZODIAC_COUNT) {
        return NULL;
    }
    return signs[index];
}

static int display_zodiac(int year)
{
    const char *sign;

    if (year < MIN_YEAR || year > MAX_YEAR) {
        fprintf(stderr, "Error: year must be between %d and %d.\n", MIN_YEAR, MAX_YEAR);
        return -1;
    }
    sign = get_chinese_zodiac(year);
    if (sign == NULL) {
        fprintf(stderr, "Error: could not determine zodiac sign.\n");
        return -1;
    }
    if (printf("%s\n", sign) < 0) {
        return -1;
    }
    if (fflush(stdout) != 0) {
        return -1;
    }
    return 0;
}

static int parse_year(const char *text, int *out_year)
{
    char *endptr;
    long value;

    if (text == NULL || out_year == NULL) {
        return -1;
    }
    while (isspace((unsigned char)*text)) {
        text++;
    }
    if (*text == '\0') {
        return -1;
    }
    errno = 0;
    value = strtol(text, &endptr, 10);
    if (errno == ERANGE || endptr == text) {
        return -1;
    }
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    if (*endptr != '\0') {
        return -1;
    }
    if (value < (long)INT_MIN || value > (long)INT_MAX) {
        return -1;
    }
    *out_year = (int)value;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2 || size > (size_t)INT_MAX) {
        return -1;
    }
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }
    buffer[size - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
    return 0;
}

int main(int argc, const char *argv[])
{
    int year;

    if (argc > 1 && argv[1] != NULL) {
        if (parse_year(argv[1], &year) != 0) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[INPUT_BUFFER_SIZE];

        if (read_line(buffer, sizeof(buffer)) != 0) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
        if (parse_year(buffer, &year) != 0) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    }
    if (display_zodiac(year) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}