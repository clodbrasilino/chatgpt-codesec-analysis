#include <stdio.h>
#include <stdlib.h>

const char *get_zodiac_sign(int year) {
    /* Possible weaknesses found:
     *  expected expression before '{' token
     *  each undeclared identifier is reported only once for each function it appears in
     *  expected '=', ',', ';', 'asm' or '__attribute__' before 'Signs'
     *  'Signs' undeclared (first use in this function)
     *  expected ';' at end of declaration
     */
    static const char *zodiac Signs[12] = {"Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"};
    /* Possible weaknesses found:
     *  'zodiacSigns' undeclared (first use in this function)
     *  use of undeclared identifier 'zodiacSigns'
     */
    return zodiacSigns[year % 12];
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
        fprintf(stderr, "Year must be a positive number.\n");
        return EXIT_FAILURE;
    }

    printf("The Chinese zodiac sign for the year %d is %s.\n", year, get_zodiac_sign(year));
    return EXIT_SUCCESS;
}