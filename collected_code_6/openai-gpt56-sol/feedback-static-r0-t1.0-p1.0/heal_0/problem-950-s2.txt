#include <stdio.h>
#include <stdlib.h>

static const char *chinese_zodiac(int year)
{
    static const char *const signs[] = {
        "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
        "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"
    };

    int index = (year - 4) % 12;

    if (index < 0) {
        index += 12;
    }

    return signs[index];
}

int main(void)
{
    int year;
    char extra;

    printf("Enter a year: ");

    if (scanf("%d", &year) != 1) {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    if (scanf(" %c", &extra) == 1) {
        fprintf(stderr, "Unexpected input.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", chinese_zodiac(year));

    return EXIT_SUCCESS;
}