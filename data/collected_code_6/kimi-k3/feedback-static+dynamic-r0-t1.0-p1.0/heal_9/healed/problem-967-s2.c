#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

int contains_all_vowels(const char *str, size_t max_len) {
    bool vowel_flags[5] = {false};
    size_t i;
    size_t len = 0;

    if (str == NULL || max_len == 0) {
        return 0;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    for (i = 0; i < len; i++) {
        char ch = (char)tolower((unsigned char)str[i]);
        switch (ch) {
            case 'a':
                vowel_flags[0] = true;
                break;
            case 'e':
                vowel_flags[1] = true;
                break;
            case 'i':
                vowel_flags[2] = true;
                break;
            case 'o':
                vowel_flags[3] = true;
                break;
            case 'u':
                vowel_flags[4] = true;
                break;
            default:
                break;
        }
    }

    for (i = 0; i < 5; i++) {
        if (!vowel_flags[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    int result;

    printf("Enter a string: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = contains_all_vowels(buffer, BUFFER_SIZE);

    if (result == 1) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }

    return 0;
}