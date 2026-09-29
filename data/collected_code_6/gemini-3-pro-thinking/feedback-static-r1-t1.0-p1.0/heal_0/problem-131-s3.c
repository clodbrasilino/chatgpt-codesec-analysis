#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_vowel(char c) {
    unsigned char uc = (unsigned char)c;
    uc = (unsigned char)tolower(uc);
    return (uc == 'a' || uc == 'e' || uc == 'i' || uc == 'o' || uc == 'u');
}

void reverse_vowels(char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0) {
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
    char test_string_1[] = "Hello World";
    char test_string_2[] = "Software Engineering";
    char test_string_3[] = "AEIOUaeiou";
    char test_string_4[] = "xyz";
    char test_string_5[] = "";

    reverse_vowels(test_string_1);
    printf("%s\n", test_string_1);

    reverse_vowels(test_string_2);
    printf("%s\n", test_string_2);

    reverse_vowels(test_string_3);
    printf("%s\n", test_string_3);

    reverse_vowels(test_string_4);
    printf("%s\n", test_string_4);

    reverse_vowels(test_string_5);
    printf("%s\n", test_string_5);

    reverse_vowels(NULL);

    return 0;
}