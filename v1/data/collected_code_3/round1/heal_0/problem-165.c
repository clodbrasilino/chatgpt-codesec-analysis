#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countCharsAtSamePosition(char* str) {
    int count = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(i == tolower(str[i]) - 'a' || i == toupper(str[i]) - 'A') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Alphabet";
    printf("Number of characters at same position as in English alphabet: %d\n", countCharsAtSamePosition(str));
    return 0;
}