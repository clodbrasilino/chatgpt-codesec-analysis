#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LENGTH 101

void remove_parenthesis_area(char* string, size_t length) {
    int i, j = 0;
    int count = 0;

    if(string == NULL) {
        fprintf(stderr, "Invalid pointer passed as parameter.");
        return;
    }

    for (i = 0; i < length && string[i] != '\0'; i++) {

        if (string[i] == '(') {
            count++;
            continue;
        }
        else if (string[i] == ')') {
            count--;
            if (count == 0) {
                continue;
            }
        }

        if (j < length - 1) {
            string[j++] = string[i];
        } else {
            break;
        }  
    }

    string[j] = '\0';
}

int main() {
    char* string = calloc(STRING_LENGTH, sizeof(char));
    if (string == NULL) {
        fprintf(stderr, "Failed to allocate memory.");
        return 1;
    }

    strncpy(string, "This (is) a string (with) parenthesis.", STRING_LENGTH - 1);
    string[STRING_LENGTH - 1] = '\0';

    size_t length = strlen(string);
    if(length >= STRING_LENGTH) {
        fprintf(stderr, "Input string is too long.");
        free(string);
        return 1;
    }

    remove_parenthesis_area(string, length);

    if ( string != NULL ){
        printf("%s\n", string);
        free(string);
    }

    return 0;
}