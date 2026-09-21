#include <stdio.h>
#include <stdlib.h>

int get_ascii_value(unsigned char c) {
    return (int)c;
}

int main(void) {
    unsigned char input;
    
    if (fread(&input, 1, 1, stdin) != 1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", get_ascii_value(input));

    return EXIT_SUCCESS;
}