#include <stdio.h>
#include <string.h>

#define MAX_SIZE 101

int countUpperCaseChars(const char *str, int len) {
    int count = 0;
    if (str == NULL){
        return count;
    }

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

        int len = strnlen(str, MAX_SIZE - 1);

        int result = countUpperCaseChars(str, len);
        printf("Number of upper case characters: %d\n", result);
    }

    return 0;
}