#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

void replace_chars(char* str, int n) {
    int i = 0;
    int replaced = 0;
    
    while(str[i] != '\0' && replaced < n) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            replaced++;
        }
        i++;
    }
}

int main() {
    char str[MAX_LENGTH] = "This is a plain, normal, boring sentence.";
    int n = 3;
    
    printf("Original: %s\n", str);
    
    replace_chars(str, n);
    
    printf("Modified: %s\n", str);
    
    return 0;
}