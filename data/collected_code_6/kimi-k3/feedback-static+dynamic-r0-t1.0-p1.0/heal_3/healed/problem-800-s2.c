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
    size_t size = 0;

    printf("Enter a string: ");
    if (getline(&input, &size, stdin) == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    printf("Original string: \"%s\"\n", input);
    remove_whitespaces(input);
    printf("String without whitespaces: \"%s\"\n", input);

    free(input);
    return EXIT_SUCCESS;
}