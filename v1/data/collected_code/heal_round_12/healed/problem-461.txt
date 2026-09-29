#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 102

int countUpperCaseChars(const char *str) {
    int count = 0;
    if (str == NULL){
        return count;
    }
    
    int len = strnlen(str, MAX_SIZE);
    for (int i = 0; i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[MAX_SIZE];

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin)) {
        str[strcspn(str, "\n")] = '\0';
        int result = countUpperCaseChars(str);
        printf("Number of upper case characters: %d\n", result);
    }
    return 0;
}