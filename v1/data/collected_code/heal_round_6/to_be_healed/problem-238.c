#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 101

int countSubstrings(const char* str, int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            count++;
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_LEN] = {'\0'};
    
    printf("Enter a string: ");
    
    if (fgets(str, MAX_STR_LEN, stdin) == NULL) return 1;
    str[strcspn(str, "\n")] = '\0';
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (str[strlen(str)] != '\0') {
        printf("The string is not zero terminated\n");
        return 1;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);
    if(length >= MAX_STR_LEN) {
        printf("Input exceeds maximum string length\n");
        return 1;
    }

    int result = countSubstrings(str, length);
    printf("Number of non-empty substrings: %d\n", result);

    return 0;
}