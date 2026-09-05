#include <stdio.h>
#include <stdlib.h>

const char *get_zodiac_sign(int year) {
    if (year < 0) {
        return NULL;
    }
    switch (year % 12) {
        case 0: return "Monkey";
        case 1: return "Rooster";
        case 2: return "Dog";
        case 3: return "Pig";
        case 4: return "Rat";
        case 5: return "Ox";
        case 6: return "Tiger";
        case 7: return "Rabbit";
        case 8: return "Dragon";
        case 9: return "Snake";
        case 10: return "Horse";
        case 11: return "Goat";
        default: return NULL;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long year_long = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || year_long < 0 || year_long > 2147483647) {
        fprintf(stderr, "Invalid year input\n");
        return EXIT_FAILURE;
    }
    int year = (int)year_long;
    const char *sign = get_zodiac_sign(year);
    if (sign == NULL) {
        fprintf(stderr, "Could not determine zodiac sign\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", sign);
    return EXIT_SUCCESS;
}