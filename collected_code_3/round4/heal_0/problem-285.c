#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if(str[i] == 'a' && i+2 < length && str[i+1] == 'b' && str[i+2] == 'b') {
            if(i+3 < length && str[i+3] == 'b') {
                return true;
            }
            else if(i+3 == length) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    if(match_pattern(str)) {
        printf("The string matches the pattern.\n");
    } else {
        printf("The string does not match the pattern.\n");
    }
    return 0;
}