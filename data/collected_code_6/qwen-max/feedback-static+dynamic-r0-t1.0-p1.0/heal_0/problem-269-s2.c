#include <stdio.h>

int get_ascii_value(char c) {
    return (int)c;
}

int main() {
    char ch;
    printf("Enter a character: ");
    scanf("%c", &ch);
    int ascii = get_ascii_value(ch);
    printf("Ascii value of '%c' is %d\n", ch, ascii);
    return 0;
}