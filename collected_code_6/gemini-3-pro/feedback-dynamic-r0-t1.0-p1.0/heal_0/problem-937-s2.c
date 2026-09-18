#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_most_common_character(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    int counts[256] = {0};
    int max_count = 0;
    char most_common = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            most_common = (char)c;
        }
    }

    return most_common;
}

int main() {
    const char *test_str = "hello world!";
    
    char result = find_most_common_character(test_str);
    
    if (result != '\0') {
        printf("Most common character: '%c'\n", result);
    } else {
        printf("Invalid input or empty string.\n");
    }

    return 0;
}