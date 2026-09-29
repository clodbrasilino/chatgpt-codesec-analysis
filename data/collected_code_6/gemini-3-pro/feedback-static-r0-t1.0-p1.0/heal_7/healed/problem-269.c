#include <stdio.h>
#include <stdlib.h>

int get_ascii_value(unsigned char c) {
    return (int)c;
}

int main(void) {
    int input = fgetc(stdin);

    if (input == EOF) {
        return EXIT_FAILURE;
    }

    printf("%d\n", get_ascii_value((unsigned char)input));

    return EXIT_SUCCESS;
}