#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_most_common_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    int counts[256] = {0};
    int max_count = 0;
    char most_common = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char current_char = (unsigned char)str[i];
        counts[current_char]++;
        
        if (counts[current_char] > max_count) {
            max_count = counts[current_char];
            most_common = (char)current_char;
        }
    }

    return most_common;
}

int main(void) {
    const char *test_string = "hello world";
    char result = find_most_common_char(test_string);
    
    if (result != '\0') {
        printf("Most common character: '%c'\n", result);
    } else {
        printf("Invalid or empty string.\n");
    }

    return 0;
}