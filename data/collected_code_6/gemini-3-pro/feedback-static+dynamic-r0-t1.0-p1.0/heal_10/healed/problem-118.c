#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    int ch;
    int in_word = 0;
    int first = 1;

    if (putchar('[') == EOF) {
        return EXIT_FAILURE;
    }
    
    while ((ch = fgetc(stdin)) != EOF) {
        if (isspace((unsigned char)ch)) {
            if (in_word) {
                if (putchar('\'') == EOF) {
                    return EXIT_FAILURE;
                }
                in_word = 0;
            }
        } else {
            if (!in_word) {
                if (!first) {
                    if (fputs(", ", stdout) == EOF) {
                        return EXIT_FAILURE;
                    }
                }
                if (putchar('\'') == EOF) {
                    return EXIT_FAILURE;
                }
                first = 0;
                in_word = 1;
            }
            if (putchar(ch) == EOF) {
                return EXIT_FAILURE;
            }
        }
    }
    
    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }
    
    if (in_word) {
        if (putchar('\'') == EOF) {
            return EXIT_FAILURE;
        }
    }
    
    if (fputs("]\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}