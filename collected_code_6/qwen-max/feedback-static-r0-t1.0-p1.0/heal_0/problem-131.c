#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_vowel(char c) {
    char lower_c = tolower(c);
    return lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u';
}

void reverse_vowels(char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    while (start < end) {
        if (!is_vowel(str[start])) {
            start++;
        } else if (!is_vowel(str[end])) {
            end--;
        } else {
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start++;
            end--;
        }
    }
}

int main() {
    char input[] = "hello world";
    reverse_vowels(input);
    printf("%s\n", input);
    return 0;
}