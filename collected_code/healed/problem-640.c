#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LENGTH 101

void remove_parenthesis_area(char* string, size_t length) {
    int i, j = 0;
    int count = 0;

    for (i = 0; i < length; i++) {
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

        string[j++] = string[i];   
    }

    string[j] = '\0';
}

int main() {
    char string[STRING_LENGTH] = "This (is) a string (with) parenthesis.";
    remove_parenthesis_area(string, strlen(string));
    printf("%s\n", string);

    return 0;
}