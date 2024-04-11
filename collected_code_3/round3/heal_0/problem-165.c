#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_chars_same_position(char* str) {
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
    printf("Number of characters at same position as in English alphabet: %d\n", count_chars_same_position(str));
    return 0;
}