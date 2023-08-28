#include <stdio.h>

int checkAllVowels(char str[]) {
    int vowelCount = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
            vowelCount++;
        }
        i++;
    }
    
    if (vowelCount == 5) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    scanf("%s", str);
    
    if (checkAllVowels(str)) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }
    
    return 0;
}