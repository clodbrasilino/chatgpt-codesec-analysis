#include <stdio.h>
#include <ctype.h>
#include <string.h>

void remove_spaces(char* input) {
    int count = 0;
    for (int i = 0; input[i]; i++) {
        if (!isspace(input[i])) {
            input[count++] = input[i];
        }
    }
    input[count] = '\0';
}

int main() {
    char str[] = "Hello, remove all spaces!";
    remove_spaces(str);
    printf("%s\n", str);
    return 0;
}