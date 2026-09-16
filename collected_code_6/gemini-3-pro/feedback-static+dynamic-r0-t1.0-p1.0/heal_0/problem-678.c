#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(char *str) {
    if (str == NULL) {
        return;
    }

    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

int main(void) {
    char str[] = "H e l l o W o r l d";
    
    remove_spaces(str);
    
    printf("%s\n", str);
    
    return 0;
}