#include <stdio.h>
#include <stdlib.h>

static const char *chinese_zodiac(int year)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static const char *const signs[12] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    const int count = (int)(sizeof(signs) / sizeof(signs[0]));
    int index;

    index = year % count;
    if (index < 0) {
        index += count;
    }
    if (index < 0 || index >= count) {
        return "Unknown";
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
        fprintf(stderr, "Error: invalid input, expected an integer year.\n");
        return EXIT_FAILURE;
    }
    if (year < 1) {
        fprintf(stderr, "Error: year must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("The Chinese zodiac sign for year %d is: %s\n",
           year, chinese_zodiac(year));

    return EXIT_SUCCESS;
}