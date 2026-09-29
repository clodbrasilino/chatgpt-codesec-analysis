#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_vowel(char c);
void reverse_vowels(char *str, size_t max_len);

bool is_vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void reverse_vowels(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len <= 1) {
        return;
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        while (left < right && !is_vowel(str[left])) {
            left++;
        }
        while (left < right && !is_vowel(str[right])) {
            right--;
        }
        if (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    const char source[] = "Programming in C is fun!";
    size_t source_size = sizeof(source);
    
    char *str = malloc(source_size);
    if (str == NULL) {
        return EXIT_FAILURE;
    }
    
    snprintf(str, source_size, "%s", source);
    
    reverse_vowels(str, source_size);
    
    if (printf("%s\n", str) < 0) {
        free(str);
        return EXIT_FAILURE;
    }
    
    free(str);
    
    return EXIT_SUCCESS;
}