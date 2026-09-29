#include <stdio.h>
#include <stdlib.h>

#define ZODIAC_COUNT 12
#define MIN_YEAR 1
#define MAX_YEAR 9999

static const char *get_chinese_zodiac(int year)
{
    static const char *const signs[ZODIAC_COUNT] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    int index;

    if (year < MIN_YEAR || year > MAX_YEAR) {
        return NULL;
    }

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
        fprintf(stderr, "Error: year must be between %d and %d.\n",
                MIN_YEAR, MAX_YEAR);
        return -1;
    }
    sign = get_chinese_zodiac(year);
    if (sign == NULL) {
        fprintf(stderr, "Error: could not determine zodiac sign.\n");
        return -1;
    }
    if (printf("The Chinese zodiac sign for year %d is: %s\n", year, sign) < 0) {
        return -1;
    }
    return 0;
}

int main(void)
{
    int year;
    int result;

    printf("Enter a year: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }
    result = scanf("%d", &year);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input, expected an integer year.\n");
        return EXIT_FAILURE;
    }
    if (display_zodiac(year) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}