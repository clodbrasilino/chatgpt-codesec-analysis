#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_vowel(char c) {
    c = (char)tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

char* reverse_vowels(const char* s) {
    if (s == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i <= len; i++) {
        result[i] = s[i];
    }

    if (len == 0) {
        return result;
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        while (left < right && !is_vowel(result[left])) {
            left++;
        }
        while (left < right && !is_vowel(result[right])) {
            right--;
        }

        if (left < right) {
            char temp = result[left];
            result[left] = result[right];
            result[right] = temp;
            left++;
            right--;
        }
    }

    return result;
}

int main(void) {
    const char* test_str = "hello world";
    char* reversed = reverse_vowels(test_str);
    
    if (reversed != NULL) {
        printf("Original: %s\n", test_str);
        printf("Reversed: %s\n", reversed);
        free(reversed);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}