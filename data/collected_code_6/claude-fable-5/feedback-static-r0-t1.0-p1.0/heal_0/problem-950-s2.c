#include <stdio.h>
#include <stdlib.h>

static const char *get_chinese_zodiac(int year)
{
    static const char *signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };

    if (year < 1) {
        return NULL;
    }

    return signs[year % 12];
}

int main(void)
{
    int year = 0;
    int result = 0;
    const char *sign = NULL;

    printf("Enter a year: ");

    result = scanf("%d", &year);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input, expected an integer year.\n");
        return EXIT_FAILURE;
    }

    sign = get_chinese_zodiac(year);
    if (sign == NULL) {
        fprintf(stderr, "Error: year must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("The Chinese zodiac sign for year %d is: %s\n", year, sign);

    return EXIT_SUCCESS;
}