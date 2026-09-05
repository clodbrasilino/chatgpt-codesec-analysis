#include <stdio.h>
#include <stdlib.h>

void display_chinese_zodiac(int year) {
    if (year < 0) {
        fprintf(stderr, "Invalid year\n");
        return;
    }

    const char *zodiac[] = {
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
int main(int argc, char *argv[]) {
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

    display_chinese_zodiac((int)year);

    return EXIT_SUCCESS;
}