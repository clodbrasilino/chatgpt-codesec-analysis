#include <stdio.h>
#include <string.h>

int checkAllVowels(const char str[]) {
    int vowelCount = 0;
    int i;

    for (i = 0; str[i] != '\0' && i < strlen(str); i++) {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
            vowelCount++;
        }
    }

    return (vowelCount == 5) ? 1 : 0;
}

int main() {
    char str[100] = {'\0'};

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = 0;

    if (checkAllVowels(str)) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }

    return 0;
}