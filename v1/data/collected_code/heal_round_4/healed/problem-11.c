#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_SIZE 100

bool isValidString(const char* str) {
    if (!str) {
        return false;
    }

    if(strlen(str) >= MAX_STR_SIZE) {
        return false;
    }

    return true;
}

void removeOccurrences(char* str, const char c) {
    if (!isValidString(str)) {
        return;
    }

    int i, j;
    int len = strlen(str);
    
    for(i = 0, j = 0; i < len; i++){
        if(str[i] != c){
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_STR_SIZE] = {0};
    char c;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  

    printf("Enter a character: ");
    scanf(" %c", &c);

    removeOccurrences(str, c);

    printf("Modified string: %s\n", str);

    return 0;
}