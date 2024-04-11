#include <stdio.h>
#include <string.h>

int match(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(str[i] == 'a' && str[i+1] == 'b' && str[i+2] == 'b' && str[i+3] == 'b') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    if(match(str)) {
        printf("Match found\n");
    } else {
        printf("Match not found\n");
    }
    return 0;
}