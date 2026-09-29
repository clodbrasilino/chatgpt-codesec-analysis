#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void find_sequences(const char *input) {
    if (input == NULL) {
        return;
    }

    bool in_sequence = false;

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (isupper((unsigned char)input[i])) {
            if (in_sequence) {
                printf("\n");
            }
            if (input[i + 1] != '\0' && islower((unsigned char)input[i + 1])) {
                printf("%c", input[i]);
                in_sequence = true;
            } else {
                in_sequence = false;
            }
        } else if (islower((unsigned char)input[i]) && in_sequence) {
            printf("%c", input[i]);
        } else {
            if (in_sequence) {
                printf("\n");
            }
            in_sequence = false;
        }
    }
    if (in_sequence) {
        printf("\n");
    }
}

int main(void) {
    const char *text = "This Is A TestString with Some CamelCase and PascalCase words.";
    
    find_sequences(text);
    
    return EXIT_SUCCESS;
}