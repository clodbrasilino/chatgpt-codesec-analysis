#include <stdio.h>
#include <string.h>

int countLowercaseLetters(char* str) {
    int count = 0;
    for(int i = 0; str[i]; i++) {
        if(str[i] >= 'a' && str[i] <= 'z') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello World!";
    printf("Number of lowercase letters: %d\n", countLowercaseLetters(str));
    return 0;
}