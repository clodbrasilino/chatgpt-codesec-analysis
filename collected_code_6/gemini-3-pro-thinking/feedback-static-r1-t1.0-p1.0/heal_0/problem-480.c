#include <stdio.h>

char find_max_occurring_char(const char *str);

char find_max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    int freq[256] = {0};
    int max_count = -1;
    char max_char = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char current_char = (unsigned char)str[i];
        freq[current_char]++;
        
        if (freq[current_char] > max_count) {
            max_count = freq[current_char];
            max_char = (char)current_char;
        }
    }

    return max_char;
}

int main(void) {
    const char *test_string = "character frequency test";
    char max_char = find_max_occurring_char(test_string);

    if (max_char != '\0') {
        printf("%c\n", max_char);
    } else {
        printf("Error or empty string\n");
    }

    return 0;
}