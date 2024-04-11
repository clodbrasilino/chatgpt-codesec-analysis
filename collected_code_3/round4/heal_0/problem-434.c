#include <stdio.h>
#include <string.h>

int match(char *str) {
    int length = strlen(str);
    int i = 0;
    while(i < length) {
        if(str[i] == 'a') {
            if(i+1 < length && str[i+1] == 'b') {
                while(i+1 < length && str[i+1] == 'b') {
                    i++;
                }
                return 1;
            }
        }
        i++;
    }
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    if(match(str)) {
        printf("Match found!\n");
    } else {
        printf("Match not found!\n");
    }
    return 0;
}