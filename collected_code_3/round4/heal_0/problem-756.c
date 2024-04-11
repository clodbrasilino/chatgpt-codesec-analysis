#include <stdio.h>
#include <string.h>

int match(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(str[i] == 'a') {
            if(i < len - 1 && str[i+1] == 'b') {
                return 1;
            } else if(i == len - 1 || str[i+1] != 'b') {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    if(match(str)) {
        printf("Match found\n");
    } else {
        printf("Match not found\n");
    }
    return 0;
}