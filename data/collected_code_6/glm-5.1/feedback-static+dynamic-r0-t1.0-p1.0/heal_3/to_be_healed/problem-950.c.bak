#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

void display_chinese_zodiac(int year) {
    if (year < 0) {
        fprintf(stderr, "Invalid year\n");
        return;
    }

    const char * const zodiac[] = {
        "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
        "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"
    };

    int index = (year - 4) % 12;
    if (index < 0) {
        index += 12;
    }

    printf("%s\n", zodiac[index]);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long year = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid year format\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     */
    if (year < 0 || year > INT_MAX) {
        fprintf(stderr, "Invalid year\n");
        return EXIT_FAILURE;
    }

    display_chinese_zodiac((int)year);

    return EXIT_SUCCESS;
}