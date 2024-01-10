#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrangeAdjacentDifferent(const char* str) {
    int count[26] = {0};
    int len = strlen(str);
  
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
    char str[101];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if it exist
    if (str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
    }

    if (canRearrangeAdjacentDifferent(str)) {
        printf("The letters of the given string can be rearranged so that two adjacent characters are different.\n");
    } else {
        printf("The letters of the given string cannot be rearranged to satisfy the condition.\n");
    }
    
    return 0;
}
