#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void replace_spaces(char *str, size_t size, char replacement) {
    if (str == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to replace_spaces\n");
        return;
    }

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return;
    }

    if (size == 0) {
        fprintf(stderr, "Error: Buffer size cannot be zero\n");
        return;
    }

    size_t i = 0;
    while (i < size && str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
        i++;
    }
}

int main(void) {
    char *buffer = NULL;
    char replacement;
    size_t buffer_size = 256;
    size_t input_len;
    int c;
    
    buffer = (char *)calloc(buffer_size, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter a string: ");
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    input_len = strnlen(buffer, buffer_size);
    if (input_len > 0 && buffer[input_len - 1] == '\n') {
        buffer[input_len - 1] = '\0';
    } else {
        if (input_len >= buffer_size - 1) {
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    
    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        fprintf(stderr, "Error reading replacement character\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    replace_spaces(buffer, buffer_size, replacement);
    printf("Modified string: %s\n", buffer);
    
    free(buffer);
    return EXIT_SUCCESS;
}