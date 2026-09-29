#include <stdio.h>
#include <string.h>
#include <ctype.h>

void split_string(char *str) {
    while(*str) {
        if(isupper(*str)) {
            printf("\n");
        } else {
            printf("%c", *str);
        }
        str++;
    }
}

int main() {
    char str[] = "HelloWorldThisIsASampleString";
    split_string(str);
    return 0;
}