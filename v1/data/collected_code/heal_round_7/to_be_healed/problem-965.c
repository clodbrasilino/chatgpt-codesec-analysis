#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100

void camelToSnake(char* str, int len) {
    int i, j;
    char c;

    for(i = 0, j = 0; i < len; i++, j++) {
        c = str[i]; 

        if(isupper(c)) {
            if(j+1 >= MAX_INPUT_LENGTH) {
                printf("Converted string is too long.\n");
                exit(1);
            }
            str[j] = '_';
            str[++j] = tolower(c);
        } else {
            str[j] = c;
        }
    }

    if(j < MAX_INPUT_LENGTH) {
        str[j] = '\0';
    } 
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_INPUT_LENGTH+1];

    printf("Enter a camel case string: ");
    if(fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error in input.\n");
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(strlen(str) > MAX_INPUT_LENGTH) {
        printf("Input string is too long.\n");
        return 1;
    } else {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        camelToSnake(str, strlen(str));
    }

    printf("The snake case string is: %s\n", str);
    
    return 0;
}