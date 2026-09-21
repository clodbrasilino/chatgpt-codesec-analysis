#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

char *reverseVowels(char *s) {
    if (s == NULL || *s == '\0') {
        return s;
    }
    const char *vowels = "aeiouAEIOU";
    char *left = s;
    char *right = s;
    size_t len = 0;
    while (*right != '\0' && len < MAX_STRING_LENGTH) {
        right++;
        len++;
    }
    if (len == 0) {
        return s;
    }
    right--;
    while (left < right) {
        while (left < right && strchr(vowels, (unsigned char)*left) == NULL) {
            left++;
        }
        while (left < right && strchr(vowels, (unsigned char)*right) == NULL) {
            right--;
        }
        if (left < right) {
            char temp = *left;
            *left = *right;
            *right = temp;
            left++;
            right--;
        }
    }
    return s;
}

int main(void) {
    char str[] = "hello world";
    printf("%s\n", reverseVowels(str));
    return 0;
}