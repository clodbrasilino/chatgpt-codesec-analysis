#include <stdio.h>
#include <stdlib.h>

const char* get_chinese_zodiac(int year) {
    const char* zodiac_signs[] = {
        "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
        "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"
    };
    
    if (year < 1900) {
        return "Invalid year (must be >= 1900)";
    }
    
    return zodiac_signs[(year - 1900) % 12];
}

int main(void) {
    int year;
    char buffer[100];
    char* endptr;
    
    printf("Enter a year (>= 1900): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    year = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || *endptr != '\n') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }
    
    printf("Chinese Zodiac: %s\n", get_chinese_zodiac(year));
    
    return EXIT_SUCCESS;
}