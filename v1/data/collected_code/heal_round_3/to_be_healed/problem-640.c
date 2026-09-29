#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LENGTH 101

void remove_parenthesis_area(char* string, size_t length) {
    int i, j = 0;
    int count = 0;

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

        if (j < STRING_LENGTH - 1) {
            string[j++] = string[i];
        } else {
            break;
        }  
    }

    string[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string[STRING_LENGTH] = "This (is) a string (with) parenthesis.";
    size_t length = strnlen(string, STRING_LENGTH);

    remove_parenthesis_area(string, length);
    printf("%s\n", string);

    return 0;
}