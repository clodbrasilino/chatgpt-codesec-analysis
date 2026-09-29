#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countNumericValues(const char *string) {
    int count = 0;
    if (string == NULL) {
        return 0;
    }
    for (int i = 0; string[i] != '\0'; i++) {
        if (isdigit(string[i])) {
            count++;
        }
    }
    return count;
}

int main(void) {
    char string[100];
    printf("Enter a string:\n");
    if(fgets(string, 100, stdin) != NULL){
        printf("Number of numeric values in the string: %d\n", countNumericValues(string));
    }
    return 0;
}