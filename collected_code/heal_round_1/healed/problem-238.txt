#include <stdio.h>
#include <string.h>

int countSubstrings(const char* str) {
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
    char str[101];
    printf("Enter a string: ");
    fgets(str, 101, stdin);
   
    if(str[strlen(str)-1] == '\n')
     str[strlen(str)-1] = 0;
   
    int result = countSubstrings(str);
    printf("Number of non-empty substrings: %d\n", result);

    return 0;
}