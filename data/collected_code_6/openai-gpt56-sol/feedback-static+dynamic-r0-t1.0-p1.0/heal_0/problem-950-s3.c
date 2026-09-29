#include <stdio.h>
#include <stdlib.h>

static const char *chinese_zodiac(int year)
{
    static const char *const signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox",
        "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat"
    };
    int index = year % 12;

    if (index < 0) {
        index += 12;
    }

    return signs[index];
}

int main(void)
{
    int year;
    int result;

    printf("Enter a year: ");
    result = scanf("%d", &year);

    if (result != 1) {
        fprintf(stderr, "Invalid year input.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", chinese_zodiac(year));
    return EXIT_SUCCESS;
}