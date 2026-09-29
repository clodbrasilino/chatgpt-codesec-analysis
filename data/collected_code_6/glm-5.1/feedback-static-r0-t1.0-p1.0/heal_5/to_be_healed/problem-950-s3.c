#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

const char* get_zodiac_sign(unsigned int year) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };

    return signs[year % 12];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    unsigned long year;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    year = strtoul(argv[1], &endptr, 10);

    /* Possible weaknesses found:
     *  'UINT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'UINT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (errno != 0 || *endptr != '\0' || year > UINT_MAX) {
        fprintf(stderr, "Invalid year format\n");
        return EXIT_FAILURE;
    }

    const char* sign = get_zodiac_sign((unsigned int)year);

    printf("%s\n", sign);

    return EXIT_SUCCESS;
}