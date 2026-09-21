#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
const char *zodiacSigns[12] = {"Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"};

const char *get_zodiac_sign(int year) {
    return zodiacSigns[year % 12];
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long year = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     */
    if (year <= 0 || *endptr != '\0' || year > INT_MAX) {
        fprintf(stderr, "Year must be a positive number and within the range of an int.\n");
        return EXIT_FAILURE;
    }

    printf("The Chinese zodiac sign for the year %ld is %s.\n", year, get_zodiac_sign((int)year));
    return EXIT_SUCCESS;
}