#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ZODIAC_COUNT 12

static const char *chinese_zodiac(int year)
{
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
        return "Unknown";
    }
    return signs[index];
}

static int parse_year(const char *text, int *out_year)
{
    char *endptr;
    long value;

    if (text == NULL || out_year == NULL) {
        return 0;
    }

    errno = 0;
    endptr = NULL;
    value = strtol(text, &endptr, 10);

    if (errno != 0 || endptr == text) {
        return 0;
    }

    while (*endptr == ' ' || *endptr == '\t' ||
           *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        return 0;
    }

    if (value < INT_MIN || value > INT_MAX) {
        return 0;
    }

    *out_year = (int)value;
    return 1;
}

int main(int argc, char const *argv[])
{
    int year;

    if (argc > 1) {
        if (!parse_year(argv[1], &year)) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    } else {
        char buffer[64];

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
        if (!parse_year(buffer, &year)) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", chinese_zodiac(year));

    return EXIT_SUCCESS;
}