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
    return zodiac_signs[((year % 12) + 12) % 12];
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100];
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
            return 0;
        }
        
        buffer[strcspn(buffer, "\n")] = '\0';
        
        errno = 0;
        long year_long = strtol(buffer, &endptr, 10);
        
        if (endptr != buffer && errno == 0 && *endptr == '\0' && 
            year_long >= INT_MIN && year_long <= INT_MAX) {
            int year = (int)year_long;
            printf("%s\n", get_chinese_zodiac(year));
        }
    }

    return 0;
}