#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_even_length(const char *word) {
    if (word == NULL) {
        return false;
    }

    size_t length = 0;
    while (word[length] != '\0') {
        length++;
    }

    return (length % 2 == 0);
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    
    if (getline(&input, &bufsize, stdin) != -1) {
        size_t len = 0;
        while (input[len] != '\0') {
            if (input[len] == '\n') {
                input[len] = '\0';
                break;
            }
            len++;
        }

        if (is_even_length(input)) {
            printf("Even\n");
        } else {
            printf("Odd\n");
        }
    }

    free(input);
    return EXIT_SUCCESS;
}