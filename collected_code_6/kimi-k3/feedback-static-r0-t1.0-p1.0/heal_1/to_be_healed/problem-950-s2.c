#include <stdio.h>
#include <stdlib.h>

const char* get_chinese_zodiac(int year) {
    const char* zodiac_signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat", 
        "Ox", "Tiger", "Rabbit", "Dragon", "Snake", 
        "Horse", "Goat"
    };
    return zodiac_signs[abs(year) % 12];
}

int main(void) {
    /* Possible weaknesses found:
     *  The scope of the variable 'year' can be reduced. [variableScope]
     */
    int year;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100];
    char *endptr;

    printf("Enter a year: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        year = (int)strtol(buffer, &endptr, 10);
        
        if (endptr != buffer) {
            printf("The Chinese Zodiac sign for %d is: %s\n", year, get_chinese_zodiac(year));
        } else {
            printf("Invalid input.\n");
        }
    }

    return 0;
}