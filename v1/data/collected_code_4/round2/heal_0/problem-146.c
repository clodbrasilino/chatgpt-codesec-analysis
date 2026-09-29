#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ascii_value_of_total_chars(char *str) {
    int ascii_total = 0;
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        ascii_total += (int)str[i];
    }
    return ascii_total;
}

int main() {
    char str[] = "Hello, World!";
    int ascii_total = ascii_value_of_total_chars(str);
    printf("The ASCII value of the total characters in '%s' is: %d\n", str, ascii_total);

    return 0;
}