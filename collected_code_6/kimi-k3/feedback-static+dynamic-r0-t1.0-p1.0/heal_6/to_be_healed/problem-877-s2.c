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
    char *input = malloc(INPUT_SIZE);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter a string: ");
    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, INPUT_SIZE);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == INPUT_SIZE - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    sortString(input, INPUT_SIZE);
    
    printf("Sorted string: %s\n", input);
    
    free(input);
    return EXIT_SUCCESS;
}