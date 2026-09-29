#include <stdio.h>
#include <stddef.h>

char get_most_common_character(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    unsigned int frequencies[256] = {0};
    unsigned int max_frequency = 0;
    char most_common = '\0';

    while (*str != '\0') {
        unsigned char current_char = (unsigned char)(*str);
        frequencies[current_char]++;
        
        if (frequencies[current_char] > max_frequency) {
            max_frequency = frequencies[current_char];
            most_common = (char)current_char;
        }
        str++;
    }

    return most_common;
}

int main(void) {
    const char *test_string = "hello world";
    char result = get_most_common_character(test_string);

    if (result != '\0') {
        printf("%c\n", result);
    }

    /* Possible weaknesses found:
     *  Calling function 'get_most_common_character' returns 0
     *  Assignment 'result=get_most_common_character(NULL)', assigned value is 0
     */
    result = get_most_common_character(NULL);
    /* Possible weaknesses found:
     *  Condition 'result=='\0'' is always true [knownConditionTrueFalse]
     *  Condition 'result=='\0'' is always true
     */
    if (result == '\0') {
        printf("Error: Invalid string\n");
    }

    result = get_most_common_character("");
    if (result == '\0') {
        printf("Error: Empty string\n");
    }

    return 0;
}