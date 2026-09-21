#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define BUFFER_SIZE 100

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
    char buffer[BUFFER_SIZE];
    char* endptr;
    long temp_year;
    int year;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input: input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    temp_year = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }
    
    if (errno == ERANGE || temp_year > INT_MAX || temp_year < INT_MIN) {
        fprintf(stderr, "Invalid input: number out of range\n");
        return EXIT_FAILURE;
    }
    
    year = (int)temp_year;
    
    printf("%s\n", get_chinese_zodiac(year));
    
    return EXIT_SUCCESS;
}