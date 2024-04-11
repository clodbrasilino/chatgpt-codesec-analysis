#include <stdio.h>
#include <string.h>

void remove_odd_index(char *str) {
    int len = strlen(str);
    int index = 0;
    for(int i = 0; i < len; i++) {
        if(i % 2 == 0) {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    remove_odd_index(str);
    printf("String after removing characters at odd index: %s\n", str);
    return 0;
}