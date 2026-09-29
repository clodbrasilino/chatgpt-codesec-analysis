#include <stdio.h>

int countUpperCaseChars(char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    int result = countUpperCaseChars(str);
    printf("Number of upper case characters: %d\n", result);

    return 0;
}