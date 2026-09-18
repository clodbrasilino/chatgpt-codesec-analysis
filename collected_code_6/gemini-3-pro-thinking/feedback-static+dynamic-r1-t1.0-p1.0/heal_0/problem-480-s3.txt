#include <stdio.h>

#define ASCII_SIZE 256

char get_max_occurring_char(const char *str);

char get_max_occurring_char(const char *str) {
    int freq[ASCII_SIZE] = {0};
    int max_freq = -1;
    char max_char = '\0';
    int i = 0;

    if (str == NULL || str[0] == '\0') {
        return '\0';
    }

    while (str[i] != '\0') {
        freq[(unsigned char)str[i]]++;
        i++;
    }

    for (i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (char)i;
        }
    }

    return max_char;
}

int main(void) {
    const char *test_str = "character frequency test string";
    char result;

    result = get_max_occurring_char(test_str);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("\n");
    }

    return 0;
}