#include <stdio.h>
#include <string.h>

void removeSpaces(char* str) {
    if (!str) return;
    
    int i = 0, j = 0;

    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc > 1 && argv[1][0] != '\0') {
        removeSpaces(argv[1]);
        printf("%s\n", argv[1]);
    }

    return 0;
}