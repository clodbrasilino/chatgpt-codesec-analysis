#include <stdio.h>
#include <string.h>

int countVowelNeighbors(char* str) {
    int count = 0;
    int len = strlen(str);

    for(int i = 1; i < len - 1; i++) {
        if((str[i-1] == 'a' || str[i-1] == 'e' || str[i-1] == 'i' || str[i-1] == 'o' || str[i-1] == 'u' ||
            str[i-1] == 'A' || str[i-1] == 'E' || str[i-1] == 'I' || str[i-1] == 'O' || str[i-1] == 'U') &&
           (str[i+1] == 'a' || str[i+1] == 'e' || str[i+1] == 'i' || str[i+1] == 'o' || str[i+1] == 'u' ||
            str[i+1] == 'A' || str[i+1] == 'E' || str[i+1] == 'I' || str[i+1] == 'O' || str[i+1] == 'U')) {
            count++;
        }
    }

    return count;
}

int main() {
    char str[] = "Hello, I am a C developer";
    printf("Number of characters with vowel neighbors: %d\n", countVowelNeighbors(str));
    return 0;
}