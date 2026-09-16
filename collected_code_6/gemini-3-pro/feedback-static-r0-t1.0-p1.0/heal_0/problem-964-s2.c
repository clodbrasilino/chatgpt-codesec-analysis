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
    char input[256];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
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

    return EXIT_SUCCESS;
}