#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void split_string(char *str) {
    int i, len = strlen(str);
    for(i = 0; i < len; i++) {
        if(isupper(str[i])) {
            printf("\n");
        }
        printf("%c", str[i]);
    }
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    split_string(str);
    return 0;
}