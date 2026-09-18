#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 1000
#define TOTAL_STRINGS 10

bool isPalindrome(char str[]) {
    int start = 0;
    int end = strlen(str) - 1;

    while (end > start) {
        if (str[start++] != str[end--])
            return false;
    }

    return true;
}

void findPalindromes(char list[TOTAL_STRINGS][MAX_STRING_LENGTH]) {
    for (int i = 0; i < TOTAL_STRINGS; i++) {
        if (isPalindrome(list[i])) {
            printf("Palindrome String Found: %s\n", list[i]);
        }
    }
}

int main() {
    char list[TOTAL_STRINGS][MAX_STRING_LENGTH];

    for (int i = 0; i < TOTAL_STRINGS; i++) {
        printf("Enter string %d: ", i + 1);
        fgets(list[i], MAX_STRING_LENGTH, stdin);
        list[i][strcspn(list[i], "\n")] = '\0';
    }

    findPalindromes(list);

    return 0; 
}