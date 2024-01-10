#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalizeFirstAndLastLetters(char *str) {
    int i;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    
    for (i = 0; i < len; i++) {
        if (i == 0 || isblank(str[i - 1])) {
            str[i] = toupper(str[i]);
        }
    }
    
    for (i = 0; i < len; i++) {
        if (isalpha(str[i]) && (i == len - 1 || isblank(str[i + 1]))) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[101];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    capitalizeFirstAndLastLetters(str);
    
    printf("Modified string: %s", str);
    
    return 0;
}