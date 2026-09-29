#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static const char *chinese_zodiac(int year)
{
    static const char *const signs[] = {
        "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
        "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"
    };
    int index = year % 12;

    index = (index - 4 + 12) % 12;
    return signs[index];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    long parsed_year;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_year = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_year < INT_MIN || parsed_year > INT_MAX) {
        fprintf(stderr, "Invalid year: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%s\n", chinese_zodiac((int)parsed_year));
    return EXIT_SUCCESS;
}