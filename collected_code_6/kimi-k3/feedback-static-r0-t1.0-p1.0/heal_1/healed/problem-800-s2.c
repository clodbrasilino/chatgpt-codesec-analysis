#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void remove_whitespaces(char *str) {
    if (str == NULL) {
        return;
    }

    char *read_ptr = str;
    char *write_ptr = str;

    while (*read_ptr != '\0') {
        if (!isspace((unsigned char)*read_ptr)) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;

    printf("Enter a string: ");
    
    bytes_read = getline(&input, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (bytes_read > 0 && input[bytes_read - 1] == '\n') {
        input[bytes_read - 1] = '\0';
    }

    printf("Original string: \"%s\"\n", input);
    remove_whitespaces(input);
    printf("String without whitespaces: \"%s\"\n", input);

    free(input);
    return EXIT_SUCCESS;
}