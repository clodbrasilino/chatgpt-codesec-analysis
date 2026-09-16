#include <stdio.h>
#include <stdlib.h>

int get_ascii_value(char c) {
    return (int)(unsigned char)c;
}

int main(int argc, char *argv[]) {
    char input;
    
    if (argc > 1) {
        input = argv[1][0];
    } else {
        if (scanf("%c", &input) != 1) {
            return EXIT_FAILURE;
        }
    }
    
    int result = get_ascii_value(input);
    
    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}