#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 102

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int countVowels(const char *str, int len) {
    int count = 0;

    for (int i = 0; i < len; i++) {
        if (isVowel(str[i])) {
            count++;
        }
    }

    return count;
}

int main() {
    char str[MAX_SIZE] = {0};

    printf("Enter a string: ");

    if (fgets(str, sizeof(str), stdin)) {
        str[strlen(str)-1] = '\0';

        int len = strlen(str);
        int vowels = countVowels(str, len);
        printf("Number of vowels: %d\n", vowels);
    }

    return 0;
}