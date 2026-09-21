#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    int year;
    int result;

    result = scanf("%d", &year);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input, expected an integer year.\n");
        return EXIT_FAILURE;
    }
    if (year < 1) {
        fprintf(stderr, "Error: year must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", chinese_zodiac(year));

    return EXIT_SUCCESS;
}