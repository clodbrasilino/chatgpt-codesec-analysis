#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_sequence(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        if(!(islower(str[i]) || str[i] == '_')) {
            return 0;
        }
        i++;
    }
    return 1;
}

int main() {
    char str[] = "this_is_a_test";
    if(is_sequence(str)) {
        printf("The string is a sequence of lowercase letters joined with an underscore.\n");
    } else {
        printf("The string is not a sequence of lowercase letters joined with an underscore.\n");
    }
    return 0;
}