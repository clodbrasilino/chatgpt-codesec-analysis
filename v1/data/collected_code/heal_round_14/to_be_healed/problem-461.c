#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 102

int countUpperCaseChars(const char *str, size_t length) {
    int count = 0;
    if (str == NULL) return count;
    for (size_t i = 0; i < length; ++i) {
        if (isupper((unsigned char)str[i])) count++;
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE];
    printf("Enter a string: ");
    
    if(fgets(str, sizeof(str), stdin)) {
        str[strcspn(str, "\n")] = '\0';
        int result = countUpperCaseChars(str, strnlen(str, MAX_SIZE));
        printf("Number of upper case characters: %d\n", result);
    }
    return 0;
}