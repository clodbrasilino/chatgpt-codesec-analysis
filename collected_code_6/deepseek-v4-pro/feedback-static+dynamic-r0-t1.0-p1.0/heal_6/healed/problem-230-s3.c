#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to replace_spaces\n");
        return;
    }

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main(void) {
    char buffer[4096];
    char replacement;
    size_t len;
    size_t input_len;
    int c;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    input_len = strnlen(buffer, sizeof(buffer));

    if (input_len == 0) {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    if (buffer[sizeof(buffer) - 2] != '\0' && buffer[sizeof(buffer) - 2] != '\n') {
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                if (ferror(stdin)) {
                    fprintf(stderr, "Error reading from stdin\n");
                    return EXIT_FAILURE;
                }
            }
        }
    }

    if (input_len > 0 && buffer[input_len - 1] == '\n') {
        buffer[input_len - 1] = '\0';
        input_len--;
    }

    len = strnlen(buffer, sizeof(buffer));

    if (len >= sizeof(buffer)) {
        fprintf(stderr, "Error: String exceeds buffer capacity\n");
        return EXIT_FAILURE;
    }

    printf("Enter replacement character: ");
    errno = 0;
    if (scanf(" %c", &replacement) != 1) {
        if (errno != 0) {
            fprintf(stderr, "Error reading replacement character\n");
        } else {
            fprintf(stderr, "Error: Invalid input for replacement character\n");
        }
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return EXIT_FAILURE;
    }

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return EXIT_FAILURE;
    }

    replace_spaces(buffer, replacement);
    printf("Modified string: %s\n", buffer);

    return EXIT_SUCCESS;
}