#include<stdio.h>
#include<string.h>

#define MAX_SIZE 100

void removeChar(char* str, char c) {
    if(str == NULL)
        return;

    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != c) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main() {

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE];
    char c; 

    printf("Enter a string: ");
    if(fgets(str, MAX_SIZE, stdin)) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (str[strlen(str) - 1] == '\n')
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            str[strlen(str) - 1] = '\0';
    }

    printf("Enter the character to remove: ");
    if(scanf("%c", &c)) {
        removeChar(str, c);
    }
  
    printf("String after removing character '%c': %s\n", c, str);

    return 0;
}