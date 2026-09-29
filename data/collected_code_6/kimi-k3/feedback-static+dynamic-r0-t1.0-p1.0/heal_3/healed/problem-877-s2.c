#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void sortString(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return;
    }
    
    for (size_t i = 0; i < len - 1; i++) {
        bool swapped = false;
        for (size_t j = 0; j < len - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main(void) {
    enum { INPUT_SIZE = 256 };
    char input[INPUT_SIZE];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    sortString(input, sizeof(input));
    
    printf("Sorted string: %s\n", input);
    
    return EXIT_SUCCESS;
}