#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findWords(char* str) {
    char* token = strtok(str, " ");
    while (token != NULL) {
        if (token[0] == 'a' || token[0] == 'e') {
            printf("%s\n", token);
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    char str[] = "apple banana elephant ant eat";
    findWords(str);
    return 0;
}