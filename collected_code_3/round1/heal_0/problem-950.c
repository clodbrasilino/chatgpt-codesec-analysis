#include <stdio.h>

const char* getZodiacSign(int year) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Sheep"
    };
    return signs[year % 12];
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    printf("The Chinese Zodiac sign for %d is %s\n", year, getZodiacSign(year));
    return 0;
}