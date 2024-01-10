#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 101

void camelToSnake(char* str, int len) {
    int i, j;
    char c;

    for(i = 0, j = 0; i < len; i++, j++) {
        c = str[i];

        if(isupper(c)) {
            str[j] = '_';
            str[++j] = tolower(c);
        } else {
            str[j] = c;
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_LENGTH];

    printf("Enter a camel case string: ");
    if(fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error in input.\n");
        return 1;
    }

    int len = strcspn(str, "\n");

    if(len < sizeof(str)) {
        str[len] = '\0';
    } else {
        printf("Input string is too long.\n");
        return 1;
    }

    camelToSnake(str, len);

    printf("The snake case string is: %s\n", str);

    return 0;
}