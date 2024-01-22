#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_SIZE 100

bool isValidString(const char* str) {
    if (!str) {
        return false;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(strlen(str) >= MAX_STR_SIZE) {
        return false;
    }

    return true;
}

void removeOccurrences(char* str, const char c) {
    if (!isValidString(str)) {
        return;
    }

    int i, j;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    
    for(i = 0, j = 0; i < len; i++){
        if(str[i] != c){
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_SIZE] = {0};
    char c;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  

    printf("Enter a character: ");
    scanf(" %c", &c);

    removeOccurrences(str, c);

    printf("Modified string: %s\n", str);

    return 0;
}