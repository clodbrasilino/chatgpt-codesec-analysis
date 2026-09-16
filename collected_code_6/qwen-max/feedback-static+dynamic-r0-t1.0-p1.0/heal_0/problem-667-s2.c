#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_vowels(const char *str) {
    int count = 0;
    while (*str) {
        char c = tolower((unsigned char)*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    const char *test_string = "This is a test string to count vowels.";
    int vowel_count = count_vowels(test_string);
    printf("Number of vowels: %d\n", vowel_count);
    return 0;
}