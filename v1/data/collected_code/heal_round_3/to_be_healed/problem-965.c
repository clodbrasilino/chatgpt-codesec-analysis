#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 101

void camelToSnake(char* str) {
    int i, j;
    char c;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    for(i = 0, j = 0; i < strlen(str); i++, j++) {
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
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    camelToSnake(str);

    printf("The snake case string is: %s\n", str);

    return 0;
}