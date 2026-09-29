#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_vowel(char c);
void reverse_vowels(char *str);

bool is_vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void reverse_vowels(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
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
    const char *source = "Programming in C is fun!";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(source);
    
    char *str = malloc(len + 1);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, source, len + 1);
    
    reverse_vowels(str);
    
    if (printf("%s\n", str) < 0) {
        free(str);
        return EXIT_FAILURE;
    }
    
    free(str);
    
    return EXIT_SUCCESS;
}