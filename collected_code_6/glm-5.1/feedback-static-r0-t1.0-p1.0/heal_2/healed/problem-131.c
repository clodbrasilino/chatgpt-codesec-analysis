#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

bool is_vowel(char c) {
    char lower = tolower((unsigned char)c);
    if (lower < 'a' || lower > 'z') return false;
    if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') return true;
    return false;
}

void reverse_vowels(char *s) {
    if (s == NULL) return;
    size_t len = strlen(s);
    if (len == 0) return;
    
    size_t left = 0;
    size_t right = len - 1;
    
    while (left < right) {
        while (left < right && !is_vowel(s[left])) left++;
        while (left < right && !is_vowel(s[right])) right--;
        
        if (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *input = malloc(strlen(argv[1]) + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    strcpy(input, argv[1]);
    
    reverse_vowels(input);
    printf("%s\n", input);
    
    free(input);
    input = NULL;
    
    return EXIT_SUCCESS;
}