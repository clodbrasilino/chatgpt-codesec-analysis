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

void evaluate_string(const char *str) {
    char result = get_most_common_character(str);

    if (result != '\0') {
        printf("%c\n", result);
    } else if (str == NULL) {
        printf("Error: Invalid string\n");
    } else {
        printf("Error: Empty string\n");
    }
}

int main(void) {
    evaluate_string("hello world");
    evaluate_string(NULL);
    evaluate_string("");

    return 0;
}