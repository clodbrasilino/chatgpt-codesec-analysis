#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char *argv[])
{
    int year;
    long value;
    char *endptr;

    if (argc > 1) {
        errno = 0;
        endptr = NULL;
        value = strtol(argv[1], &endptr, 10);
        if (errno != 0 || endptr == argv[1] || *endptr != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
        year = (int)value;
    } else {
        if (scanf("%d", &year) != 1) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", chinese_zodiac(year));

    return EXIT_SUCCESS;
}