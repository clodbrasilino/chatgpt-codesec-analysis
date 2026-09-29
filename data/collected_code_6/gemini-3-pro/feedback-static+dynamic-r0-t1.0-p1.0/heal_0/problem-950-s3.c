#include <stdio.h>

const char* get_chinese_zodiac(int year) {
    const char* zodiacs[] = {
        "Monkey", "Rooster", "Dog", "Pig", 
        "Rat", "Ox", "Tiger", "Rabbit", 
        "Dragon", "Snake", "Horse", "Sheep"
    };
    
    if (year < 0) {
        return "Invalid Year";
    }
    
    return zodiacs[year % 12];
}

int main(void) {
    int year;
    int items_read;

    printf("Enter a year: ");
    items_read = scanf("%d", &year);

    if (items_read != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (year < 0) {
        printf("Year must be a positive integer.\n");
        return 1;
    }

    printf("The Chinese Zodiac sign for the year %d is %s.\n", year, get_chinese_zodiac(year));

    return 0;
}