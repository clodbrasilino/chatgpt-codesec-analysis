#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100

void camelToSnake(char* str, size_t len) {
    size_t i, j;
    char c;

    for(i = 0, j = 0; i < len; i++, j++) {
        c = str[i]; 

        if(isupper(c)) {
            if(j+2 > MAX_INPUT_LENGTH) {
                printf("Converted string is too long.\n");
                exit(1);
            }
            str[j] = '_';
            str[++j] = (char)tolower(c);
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
    if (str == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter a camel case string: ");
    if(fgets(str, MAX_INPUT_LENGTH+1, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        size_t str_length = strlen(str);
    
        if(str_length <= MAX_INPUT_LENGTH) {
            camelToSnake(str, str_length);
            printf("The snake case string is: %s\n", str);
        } else {
            printf("Input string is too long.\n");
        } 

        free(str);
        return 0;
    } else {
        printf("Error in input.\n");
        free(str);
        return 1;
    }
}