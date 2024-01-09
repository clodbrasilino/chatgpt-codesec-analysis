#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Function to check if a character is lowercase
bool isLowercase(char c) {
    return (c >= 'a' && c <= 'z');
}

// Function to remove lowercase substrings from a given string
void removeLowercaseSubstrings(char* str) {
    int len = strlen(str);
    int i = 0;
    while (i < len) {
        // If current character is lowercase
        if (isLowercase(str[i])) {
            int j = i + 1;
            // Find the end of the lowercase substring
            while (j < len && isLowercase(str[j])) {
                j++;
            }
            // Remove the lowercase substring from the string
            memmove(&str[i], &str[j], len - j + 1);
            len -= (j - i);
        } else {
            i++;
        }
    }
}

// Example usage
int main() {
    char str[] = "HeLLo WOrLd";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);
    return 0;
}