#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_string(char *str) {
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if(str[i] == 'a' && (str[i+1] == 'b' && str[i+2] == 'b') || (str[i+1] == 'b' && str[i+2] == 'b' && str[i+3] == 'b')) {
            return true;
        }
    }
    return false;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    if(match_string(str)) {
        printf("The string matches the pattern.\n");
    } else {
        printf("The string does not match the pattern.\n");
    }
    return 0;
}