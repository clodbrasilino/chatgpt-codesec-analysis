#include <stdio.h>

int countCharacters(char* str) {
    int count = 0;
  
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            if (tolower(str[i]) - 'a' == i || toupper(str[i]) - 'A' == i) {
                count++;
            }
        }
    }
  
    return count;
}

int main() {
    char str[] = "aAbBcCdDeE";
    int result = countCharacters(str);
    printf("Number of characters at the same position as in English alphabet: %d", result);
  
    return 0;
}