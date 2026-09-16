#include <stdio.h>

int get_ascii_value(char c) {
    return (int)c;
}

int main(void) {
    char input_char;
    
    printf("Enter a character: ");
    if (scanf("%c", &input_char) != 1) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    printf("ASCII value of '%c' is: %d\n", input_char, get_ascii_value(input_char));
    
    return 0;
}