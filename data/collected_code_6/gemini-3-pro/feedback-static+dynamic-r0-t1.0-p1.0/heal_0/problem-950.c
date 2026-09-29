#include <stdio.h>
#include <stdlib.h>

const char* get_chinese_zodiac(int year) {
    if (year < 0) {
        return "Invalid Year";
    }

    const char* zodiacs[] = {
        "Monkey", "Rooster", "Dog", "Pig", 
        "Rat", "Ox", "Tiger", "Rabbit", 
        "Dragon", "Snake", "Horse", "Sheep"
    };

    return zodiacs[year % 12];
}

int main(void) {
    int year;
    int items_read;

    printf("Enter a year: ");
    
    items_read = scanf("%d", &year);
    
    if (items_read != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid integer.\n");
        return EXIT_FAILURE;
    }

    if (year < 0) {
        fprintf(stderr, "Error: Year cannot be negative.\n");
        return EXIT_FAILURE;
    }

    const char* sign = get_chinese_zodiac(year);
    printf("The Chinese Zodiac sign for the year %d is %s.\n", year, sign);

    return EXIT_SUCCESS;
}