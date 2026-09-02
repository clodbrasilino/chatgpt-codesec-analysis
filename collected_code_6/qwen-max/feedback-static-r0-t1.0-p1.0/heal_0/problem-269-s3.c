#include <stdio.h>

int get_ascii_value(char ch) {
    return (int)ch;
}

int main() {
    char input;
    printf("Enter a character: ");
    scanf("%c", &input);
    int ascii_value = get_ascii_value(input);
    printf("ASCII value of '%c' is %d\n", input, ascii_value);
    return 0;
}