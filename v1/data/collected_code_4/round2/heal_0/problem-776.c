#include <stdio.h>
#include <string.h>

int countCharactersWithVowelNeighbors(char *str) {
    int count = 0;
    int len = strlen(str);

    for(int i = 1; i < len - 1; ++i) {
        if((str[i - 1] == 'a' || str[i - 1] == 'A' || 
            str[i - 1] == 'e' || str[i - 1] == 'E' || 
            str[i - 1] == 'i' || str[i - 1] == 'I' || 
            str[i - 1] == 'o' || str[i - 1] == 'O' || 
            str[i - 1] == 'u' || str[i - 1] == 'U') && 
           (str[i + 1] == 'a' || str[i + 1] == 'A' || 
            str[i + 1] == 'e' || str[i + 1] == 'E' || 
            str[i + 1] == 'i' || str[i + 1] == 'I' ||
            str[i + 1] == 'o' || str[i + 1] == 'O' ||
            str[i + 1] == 'u' || str[i + 1] == 'U')) {
            ++count;
        }
    }

    return count;
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strlen(str) - 1] = '\0';

    int count = countCharactersWithVowelNeighbors(str);

    printf("Number of characters with vowels as neighbors: %d\n", count);

    return 0;
}