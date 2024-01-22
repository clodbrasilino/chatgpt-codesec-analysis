#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STR_LEN 101

void capitalizeFirstAndLastLetters(char *str) {
    if (str == NULL) 
        return;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    if (len >= MAX_STR_LEN)  
        len = MAX_STR_LEN - 1;

    for (int i = 0; i < len && str[i] != '\0'; i++) {
        if (i == 0 || str[i-1] == ' ') {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
    }

    for (int i = 0; i < len && str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i]) && (i == len - 1 || str[i+1] == ' ')) {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
    }
    str[len] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_LEN] = {'\0'};

    printf("Enter a string: ");

    if (fgets(str, sizeof(str), stdin) != NULL) {
        char *newline = strchr(str, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        capitalizeFirstAndLastLetters(str);
        printf("Modified string: %s\n", str);
        return 0;
    }

    return -1;
}