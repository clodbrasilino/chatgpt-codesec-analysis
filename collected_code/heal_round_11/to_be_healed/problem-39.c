#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LEN 101

bool canRearrangeAdjacentDifferent(char* str) {
    if (!str)
        return false;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    if (len > MAX_STRING_LEN)
        return false;

    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        if(str[i] >= 'a' && str[i] <= 'z'){
            count[str[i] - 'a'] += 1;
            if(count[str[i] - 'a'] > (len + 1) / 2) return false;
        }
    }

    return true;
}

int main() {
    char* str = malloc(MAX_STRING_LEN + 1);

    if(!str){
        printf("Memory allocation error.\n");
        return 1;
    }

    printf("Enter a string: ");
    fgets(str, MAX_STRING_LEN, stdin);

    str[strcspn(str, "\n")] = 0;

    if(canRearrangeAdjacentDifferent(str)) {
        printf("The given string can be rearranged so that two adjacent characters are different.\n");
    } else {
        printf("The letters of the given string cannot be rearranged to satisfy the condition.\n");
    }

    free(str); 
    return 0;
}