#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

const char* get_chinese_zodiac(int year) {
    static const char* const zodiac_signs[] = {
        "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
        "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"
    };
    static const size_t zodiac_count = sizeof(zodiac_signs) / sizeof(zodiac_signs[0]);
    
    if (year < 1900) {
        return "Invalid year (must be >= 1900)";
    }
    
    return zodiac_signs[(size_t)(year - 1900) % zodiac_count];
}

int main(void) {
    int year;
    long year_long;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100];
    char* endptr;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;
    /* Possible weaknesses found:
     *  The scope of the variable 'input_too_long' can be reduced. [variableScope]
     *  Variable 'input_too_long' is assigned a value that is never used. [unreadVariable]
     */
    int input_too_long = 0;
    
    printf("Enter a year (>= 1900): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        /* Possible weaknesses found:
         *  Assignment 'input_too_long=1', assigned value is 1
         */
        input_too_long = 1;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (ch == EOF) {
                break;
            }
        }
        /* Possible weaknesses found:
         *  Condition 'input_too_long' is always true [knownConditionTrueFalse]
         *  Condition 'input_too_long' is always true
         */
        if (input_too_long) {
            fprintf(stderr, "Error: input too long\n");
            return EXIT_FAILURE;
        }
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    errno = 0;
    year_long = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || year_long > INT_MAX || year_long < INT_MIN) {
        fprintf(stderr, "Invalid input: number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }
    
    year = (int)year_long;
    
    printf("Chinese Zodiac: %s\n", get_chinese_zodiac(year));
    
    return EXIT_SUCCESS;
}