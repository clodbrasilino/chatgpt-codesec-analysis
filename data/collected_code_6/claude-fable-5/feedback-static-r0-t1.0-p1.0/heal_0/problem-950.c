#include <stdio.h>
#include <stdlib.h>

static const char *get_chinese_zodiac(int year)
{
    static const char *signs[12] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    int index;

    index = year % 12;
    if (index < 0) {
        index += 12;
    }
    return signs[index];
}

static int display_zodiac(int year)
{
    const char *sign;

    if (year < 1 || year > 9999) {
        fprintf(stderr, "Error: year must be between 1 and 9999.\n");
        return -1;
    }
    sign = get_chinese_zodiac(year);
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