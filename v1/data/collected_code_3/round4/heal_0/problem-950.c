#include <stdio.h>

const char* getChineseZodiacSign(int year) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat"
    };
    return signs[year % 12];
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    printf("The Chinese Zodiac sign for year %d is %s\n", year, getChineseZodiacSign(year));
    return 0;
}