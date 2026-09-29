#include <stdio.h>
#include <stdlib.h>

const char *get_zodiac_sign(int year) {
    static const char *zodiac[] = {"Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Sheep"};
    return zodiac[(year - 4) % 12];
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int year = atoi(argv[1]);
    if (year <= 0) {
        fprintf(stderr, "Year must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    const char *sign = get_zodiac_sign(year);
    printf("The Chinese Zodiac sign for the year %d is %s.\n", year, sign);
    return EXIT_SUCCESS;
}