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
    char str[MAX_STR_LEN];

    printf("Enter a string (Maximum %d characters): ", MAX_STR_LEN - 1);

    if (fgets(str, MAX_STR_LEN, stdin) == NULL) return 1;

    str[strcspn(str, "\n")] = '\0';
    
    int length = strlen(str);
    if(length >= MAX_STR_LEN) {
        printf("Input string is too long. Please limit to %d characters\n", MAX_STR_LEN - 1);
        return 1;
    }

    int result = countSubstrings(str, length);
    printf("Number of non-empty substrings: %d\n", result);

    return 0;
}