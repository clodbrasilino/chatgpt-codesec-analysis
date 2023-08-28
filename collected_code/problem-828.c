#include <stdio.h>

void countChars(char* str) {
    int alphabets = 0;
    int digits = 0;
    int specialChars = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            alphabets++;
        } else if (str[i] >= '0' && str[i] <= '9') {
            digits++;
        } else {
            specialChars++;
        }
    }

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special Characters: %d\n", specialChars);
}

int main() {
    char str[] = "Hello123!@#";
    countChars(str);
    return 0;
}