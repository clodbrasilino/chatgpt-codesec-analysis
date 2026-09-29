#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_vowel(char c);
void reverse_vowels(char *str, size_t len);

bool is_vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void reverse_vowels(char *str, size_t len) {
    if (str == NULL || len <= 1) {
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
    size_t len = sizeof(source) - 1;
    
    char *str = malloc(len + 1);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    strncpy(str, source, len + 1);
    str[len] = '\0';
    
    reverse_vowels(str, len);
    
    if (printf("%s\n", str) < 0) {
        free(str);
        return EXIT_FAILURE;
    }
    
    free(str);
    
    return EXIT_SUCCESS;
}