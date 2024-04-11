#include <stdio.h>
#include <string.h>

void replace_chars(char *str) {
    for(int i = 0; str[i]; i++){
        if(str[i] == ' ')
            str[i] = '_';
        else if(str[i] == '_')
            str[i] = ' ';
    }
}

int main() {
    char str[] = "Hello_World This_is_a_test";
    printf("Before: %s\n", str);
    replace_chars(str);
    printf("After: %s\n", str);
    return 0;
}