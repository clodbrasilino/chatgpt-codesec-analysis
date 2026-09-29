#include <stdio.h>
#include <string.h>

int countSubstrings(const char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);
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
    char str[101];
    printf("Enter a string: ");
    fgets(str, 101, stdin);
   
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(str[strlen(str)-1] == '\n')
     /* Possible weaknesses found:
      *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
      */
     str[strlen(str)-1] = 0;
   
    int result = countSubstrings(str);
    printf("Number of non-empty substrings: %d\n", result);

    return 0;
}