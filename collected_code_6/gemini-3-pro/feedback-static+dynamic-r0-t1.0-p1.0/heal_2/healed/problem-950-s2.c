#include <stdio.h>
#include <stdlib.h>

const char* get_chinese_zodiac(int year) {
    const char* zodiac_signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", 
        "Rat", "Ox", "Tiger", "Rabbit", 
        "Dragon", "Snake", "Horse", "Sheep"
    };

    if (year < 0) {
        return NULL;
    }

    return zodiac_signs[year % 12];
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long year = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || year < 0) {
        fprintf(stderr, "Invalid year provided.\n");
        return EXIT_FAILURE;
    }

    const char* sign = get_chinese_zodiac((int)year);
    if (sign == NULL) {
        fprintf(stderr, "Error calculating zodiac sign.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", sign);

    return EXIT_SUCCESS;
}