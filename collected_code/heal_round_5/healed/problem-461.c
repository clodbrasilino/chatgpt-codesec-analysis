#include <stdio.h>
#include <string.h>

#define MAX_SIZE 101

int countUpperCaseChars(const char *str) {
    int count = 0;
    if (str == NULL){
        return count;
    }
    int len = strnlen(str, MAX_SIZE - 1);
    for (int i = 0; i < len && str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[MAX_SIZE] = {'\0'};

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin) != NULL) {
        if (str[strlen(str)-1] == '\n') {
            str[strlen(str) - 1] = 0;
        }

        int result = countUpperCaseChars(str);
        printf("Number of upper case characters: %d\n", result);
    }

    return 0;
}