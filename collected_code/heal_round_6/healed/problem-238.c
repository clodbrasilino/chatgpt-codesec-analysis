#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 101

int countSubstrings(const char* str, int length) {
    int count = 0;
    for(int i = 0; i < length; i++) {
        for(int j = i; j < length; j++) {
            count++;
        }
    }
    return count;
}

int main() {

    char str[MAX_STR_LEN] = {'\0'};

    printf("Enter a string: ");

    if (fgets(str, MAX_STR_LEN, stdin) == NULL) return 1;

    str[strcspn(str, "\n")] = '\0';
    
    if (str[strlen(str)-1] != '\0') {
        printf("The string is not zero terminated\n");
        return 1;
    }

    int length = strlen(str);
    if(length >= (MAX_STR_LEN - 1)) {
        printf("Input exceeds maximum permissible string length\n");
        return 1;
    }

    int result = countSubstrings(str, length);
    printf("Number of non-empty substrings: %d\n", result);

    return 0;
}