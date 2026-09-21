#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

const char* get_zodiac_sign(unsigned int year) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };

    return signs[year % 12];
}

int main(int argc, char * const * argv) {
    unsigned long year;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    year = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || year > UINT_MAX) {
        fprintf(stderr, "Invalid year format\n");
        return EXIT_FAILURE;
    }

    const char* sign = get_zodiac_sign((unsigned int)year);

    printf("%s\n", sign);

    return EXIT_SUCCESS;
}