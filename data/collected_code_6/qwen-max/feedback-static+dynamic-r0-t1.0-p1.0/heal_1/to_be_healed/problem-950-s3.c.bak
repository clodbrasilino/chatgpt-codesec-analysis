#include <stdio.h>
#include <stdlib.h>

char *get_zodiac_sign(int year) {
    /* Possible weaknesses found:
     *  Variable 'zodiac' can be declared as const array [constVariable]
     */
    static char *zodiac[] = {"Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Sheep"};
    return zodiac[(year - 4) % 12];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int year = atoi(argv[1]);
    if (year <= 0) {
        fprintf(stderr, "Year must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    char *sign = get_zodiac_sign(year);
    printf("The Chinese Zodiac sign for the year %d is %s.\n", year, sign);
    return EXIT_SUCCESS;
}