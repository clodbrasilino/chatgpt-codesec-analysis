#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_odd_characters(char *str) {
    if (str == NULL) {
        return;
    }

    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char input[] = "HelloWorld";
    
    remove_odd_characters(input);
    
    printf("%s\n", input);
    
    return 0;
}