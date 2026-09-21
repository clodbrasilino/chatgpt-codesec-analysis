#include <stdio.h>
#include <stdlib.h>

const char *get_zodiac_sign(int year) {
    /* Possible weaknesses found:
     *  expected expression before '{' token
     *  'Signs' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  expected ';' at end of declaration
     *  expected '=', ',', ';', 'asm' or '__attribute__' before 'Signs'
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
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

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int year = atoi(argv[1]);
    if (year <= 0) {
        fprintf(stderr, "Year must be a positive number.\n");
        return EXIT_FAILURE;
    }

    printf("The Chinese zodiac sign for the year %d is %s.\n", year, get_zodiac_sign(year));
    return EXIT_SUCCESS;
}