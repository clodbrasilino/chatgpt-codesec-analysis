#include <stdio.h>
#include <stdlib.h>

const char* get_zodiac_sign(int year) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };

    if (year < 0) {
        return NULL;
    }

    return signs[year % 12];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int year;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &year) != 1) {
        fprintf(stderr, "Invalid year format\n");
        return EXIT_FAILURE;
    }

    const char* sign = get_zodiac_sign(year);

    if (sign == NULL) {
        fprintf(stderr, "Invalid year provided\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", sign);

    return EXIT_SUCCESS;
}