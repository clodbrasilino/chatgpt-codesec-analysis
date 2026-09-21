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
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    printf("Original string: \"%s\"\n", input);
    remove_whitespaces(input);
    printf("String without whitespaces: \"%s\"\n", input);

    return EXIT_SUCCESS;
}