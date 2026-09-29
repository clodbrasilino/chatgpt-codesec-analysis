#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin)) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input.\n");
            return 0;
        }

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        errno = 0;
        long year_long = strtol(buffer, &endptr, 10);

        if (endptr != buffer && *endptr == '\0' && errno != ERANGE && 
            year_long >= INT_MIN && year_long <= INT_MAX) {
            int year = (int)year_long;
            printf("The Chinese Zodiac sign for %d is: %s\n", year, get_chinese_zodiac(year));
        } else {
            printf("Invalid input.\n");
        }
    }

    return 0;
}