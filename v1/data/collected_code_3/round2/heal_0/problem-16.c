#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_sequence(char *str) {
    int i = 0;
    while(str[i]) {
        if((str[i] >= 'a' && str[i] <= 'z') || str[i] == '_') {
            i++;
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    if(is_sequence(str)) {
        printf("The string is a sequence of lowercase letters joined with an underscore.\n");
    } else {
        printf("The string is not a sequence of lowercase letters joined with an underscore.\n");
    }
    return 0;
}