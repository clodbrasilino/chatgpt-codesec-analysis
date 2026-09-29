#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 101

void removeWhitespace(char *str) {
    
    if (!str) return;

    int i = 0, j = 0;
    int len = strnlen(str, MAX_LENGTH);

    while(i < len && str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        ++i;
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_LENGTH] = {0};
    
    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin)) {
        char* newline = strchr(str, '\n');
        if (newline) 
           *newline = '\0';
    }

    printf("Before removing whitespaces: %s\n", str);
    removeWhitespace(str);
    printf("After removing whitespaces: %s\n", str);

    return 0;
}