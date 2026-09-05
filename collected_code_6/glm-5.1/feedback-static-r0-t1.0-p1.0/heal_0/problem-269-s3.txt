#include <stdio.h>
#include <stdlib.h>

int get_ascii_value(char c) {
    return (int)(unsigned char)c;
}

int main(int argc, char *argv[]) {
    int val;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    if (argv[1][0] == '\0' || argv[1][1] != '\0') {
        return EXIT_FAILURE;
    }
    
    val = get_ascii_value(argv[1][0]);
    
    printf("%d\n", val);
    
    return EXIT_SUCCESS;
}