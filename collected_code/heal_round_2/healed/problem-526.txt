#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalizeFirstAndLastLetters(char *str) {
    if (str == NULL)
        return;
    
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (i == 0 || isblank(str[i - 1])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
    
    for (int i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i]) && (i == len - 1 || isblank((unsigned char)str[i + 1]))) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main() {
    char str[101] = {'\0'};
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        capitalizeFirstAndLastLetters(str);
        printf("Modified string: %s", str);
        return 0;
    }
    return -1;
}