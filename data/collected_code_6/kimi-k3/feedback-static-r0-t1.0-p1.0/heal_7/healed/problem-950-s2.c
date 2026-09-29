#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

const char* get_chinese_zodiac(int year) {
    const char* zodiac_signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat",
        "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
        "Horse", "Goat"
    };
    int index = year % 12;
    if (index < 0) {
        index += 12;
    }
    return zodiac_signs[index];
}

int main(void) {
    char buffer[100];
    char *endptr;

    printf("Enter a year: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        errno = 0;
        long year_long = strtol(buffer, &endptr, 10);

        if (endptr != buffer && errno != ERANGE && 
            year_long >= INT_MIN && year_long <= INT_MAX) {
            int year = (int)year_long;
            printf("The Chinese Zodiac sign for %d is: %s\n", year, get_chinese_zodiac(year));
        } else {
            printf("Invalid input.\n");
        }
    }

    return 0;
}