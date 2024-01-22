#include <stdio.h>
#include <string.h>

#define MAX_SIZE 101

int countUpperCaseChars(const char *str) {
    int count = 0;
    if (str == NULL){
        return count;
    }
    int len = strnlen(str, MAX_SIZE - 1);
    for (int i = 0; i < len && str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            count++;
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = {'\0'};

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin) != NULL) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (str[strlen(str)-1] == '\n') {
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            str[strlen(str) - 1] = 0;
        }

        int result = countUpperCaseChars(str);
        printf("Number of upper case characters: %d\n", result);
    }

    return 0;
}