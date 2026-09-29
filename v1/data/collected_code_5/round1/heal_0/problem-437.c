#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str) {
    int write_index = 0;
    for(int read_index = 0; read_index < strlen(str); read_index++) {
        if(str[read_index] % 2 == 0) {
            str[write_index++] = str[read_index];
        }
    }
    str[write_index] = '\0';
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    remove_odd_chars(str);

    printf("Result: %s\n", str);

    return 0;
}