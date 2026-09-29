#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRING_LEN 101

bool canRearrangeAdjacentDifferent(const char* str) {
    int count[26] = {0};
    int len = strnlen(str, MAX_STRING_LEN);

    for (int i = 0; i < len; i++) {
        count[str[i] - 'a']++;
    }
    
    for (int i = 0; i < 26; i++) {
        if (count[i] > (len + 1) / 2) {
            return false;
        }
    }

    return true;
}

int main() {
    char str[MAX_STRING_LEN];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        char *newline = strchr(str, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
    }
    
    if (canRearrangeAdjacentDifferent(str)) {
        printf("The given string can be rearranged so that two adjacent characters are different.\n");
    } else {
        printf("The letters of the given string cannot be rearranged to satisfy the condition.\n");
    }
    
    return 0;
}