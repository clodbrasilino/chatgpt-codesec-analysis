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
            if(j+2 > MAX_INPUT_LENGTH) {
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
    } else {
        printf("Converted string is too long.\n");
        exit(1);
    }
}

int main() {
    char* str = malloc((MAX_INPUT_LENGTH+1)*sizeof(char));

    printf("Enter a camel case string: ");
    if(fgets(str, MAX_INPUT_LENGTH+1, stdin) == NULL) {
        printf("Error in input.\n");
        free(str);
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    if(strlen(str) > MAX_INPUT_LENGTH) {
        printf("Input string is too long.\n");
        free(str);
        return 1;
    } else {
        camelToSnake(str, strlen(str) + 1);
    }

    printf("The snake case string is: %s\n", str);
    
    free(str);
    return 0;
}