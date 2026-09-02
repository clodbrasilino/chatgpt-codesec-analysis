#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_char(char *str, char ch) {
    int i, j;
    if (str == NULL) return;
    for (i = j = 0; str[i] != '\0'; ++i) {
        if (str[i] != ch) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'input="hello world"', assigned value is "hello world"
     */
    char *input = "hello world";
    char ch = 'o';
    remove_char(input, ch);
    printf("%s\n", input);
    /* Possible weaknesses found:
     *  Deallocating memory that was not dynamically allocated
     *  Deallocation of a pointer pointing to a string literal ("hello world") results in undefined behaviour. [autovarInvalidDeallocation]
     */
    free(input);
    return 0;
}