#include <stdio.h>
#include <string.h>

void remove_odd_index(char *str) {
    int i, j = 0, length;
    length = strlen(str);

    for(i = 0; i <= length; i++) {
        if(i % 2 == 0) {
            str[j++] = str[i];
        }
    }
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