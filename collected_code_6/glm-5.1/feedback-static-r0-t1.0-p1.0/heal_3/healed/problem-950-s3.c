#include <stdio.h>
#include <stdlib.h>

const char* get_zodiac_sign(unsigned int year) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };

    return signs[year % 12];
}

int main(int argc, char * const argv[const]) {
    unsigned int year;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%u", &year) != 1) {
        fprintf(stderr, "Invalid year format\n");
        return EXIT_FAILURE;
    }

    const char* sign = get_zodiac_sign(year);

    printf("%s\n", sign);

    return EXIT_SUCCESS;
}