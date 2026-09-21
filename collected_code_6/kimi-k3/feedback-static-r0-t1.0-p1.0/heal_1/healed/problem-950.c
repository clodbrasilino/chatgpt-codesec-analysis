#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
    long year_long;
    char buffer[100];
    char* endptr;
    
    printf("Enter a year (>= 1900): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    year_long = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || year_long > INT_MAX || year_long < INT_MIN) {
        fprintf(stderr, "Invalid input: number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }
    
    year = (int)year_long;
    
    printf("Chinese Zodiac: %s\n", get_chinese_zodiac(year));
    
    return EXIT_SUCCESS;
}