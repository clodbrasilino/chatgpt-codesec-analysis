#include <stdio.h>
#include <ctype.h>

void findSequences(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        if(isupper(str[i])) {
            printf("%c", str[i]);
            i++;
            while(islower(str[i])) {
                printf("%c", str[i]);
                i++;
            }
            printf("\n");
        } else {
            i++;
        }
    }
}

int main() {
    char str[] = "HelloWorldThisIsAStringWithSequences";
    findSequences(str);
    return 0;
}