#include <stdio.h>
#include <stdlib.h>

const char* getChineseZodiac(int year) {
    const char* zodiacSigns[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat", "Ox",
        "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat"
    };
    
    if (year < 0) {
        return "Invalid year";
    }
    
    return zodiacSigns[year % 12];
}

int main() {
    int year;
    
    printf("Enter a year: ");
    
    if (scanf("%d", &year) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", getChineseZodiac(year));
    
    return EXIT_SUCCESS;
}