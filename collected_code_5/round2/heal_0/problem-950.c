#include <stdio.h>

const char* get_zodiac_sign(int year) {
    const char* zodiac_signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox", 
        "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat"};

    if (year < 0) {
        return NULL;
    }

    return zodiac_signs[year % 12];
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);

    const char* sign = get_zodiac_sign(year);

    if (sign != NULL) {
        printf("The Chinese Zodiac sign for %d is %s.\n", year, sign);
    } else {
        printf("An error occurred when determining the Chinese Zodiac sign for %d.\n", year);
    }

    return 0;
}