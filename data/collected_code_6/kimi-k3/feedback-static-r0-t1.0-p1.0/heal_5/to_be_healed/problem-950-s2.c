#include <stdio.h>
#include <stdlib.h>

const char* get_chinese_zodiac(int year) {
    const char* zodiac_signs[] = {
        "Monkey", "Rooster", "Dog", "Pig", "Rat",
        "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
        "Horse", "Goat"
    };
    int index = year % 12;
    if (index < 0) {
        index += 12;
    }
    return zodiac_signs[index];
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100];
    char *endptr;

    printf("Enter a year: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int year = (int)strtol(buffer, &endptr, 10);

        if (endptr != buffer) {
            printf("The Chinese Zodiac sign for %d is: %s\n", year, get_chinese_zodiac(year));
        } else {
            printf("Invalid input.\n");
        }
    }

    return 0;
}