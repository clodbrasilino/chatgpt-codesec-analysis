#include <stdio.h>

int get_ascii_value(char c) {
    return (int)c;
}

int main(void) {
    char character;
    int ascii_value;
    int items_read;

    printf("Enter a character: ");
    items_read = scanf(" %c", &character);

    if (items_read != 1) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    ascii_value = get_ascii_value(character);
    printf("The ASCII value of '%c' is %d\n", character, ascii_value);

    return 0;
}