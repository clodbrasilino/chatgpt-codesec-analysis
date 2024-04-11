#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void split_string(char *str) {
    int i, len = strlen(str);
    char *temp = malloc(len + 1);
    int tempIndex = 0;

    for(i = 0; i < len; i++) {
        if(isupper(str[i])) {
            temp[tempIndex] = '\0';
            printf("%s\n", temp);
            tempIndex = 0;
        } else {
            temp[tempIndex++] = str[i];
        }
    }

    temp[tempIndex] = '\0';
    printf("%s\n", temp);
    free(temp);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    split_string(str);
    return 0;
}