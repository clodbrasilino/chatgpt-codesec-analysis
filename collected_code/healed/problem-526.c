#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalizeFirstAndLastLetters(char *str) {
    int i;
    int len = strlen(str);
    
    for (i = 0; i < len; i++) {
        if (i == 0 || isblank(str[i - 1])) {
            str[i] = toupper(str[i]);
        }
    }
    
    for (i = 0; i < len; i++) {
        if (isalpha(str[i]) && (i == len - 1 || isblank(str[i + 1]))) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    char str[101];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    capitalizeFirstAndLastLetters(str);
    
    printf("Modified string: %s", str);
    
    return 0;
}