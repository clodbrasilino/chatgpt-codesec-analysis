#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_sequence(char *str) {
    int i = 0;
    while(str[i]) {
        if((str[i] == '_') && islower(str[i+1])) {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    if(find_sequence(str)) {
        printf("Sequence found.\n");
    } else {
        printf("Sequence not found.\n");
    }
    return 0;
}