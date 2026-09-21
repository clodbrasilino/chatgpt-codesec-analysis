#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == EOF) {
            if (ferror(stdin)) {
                fprintf(stderr, "Error reading from stdin\n");
                clearerr(stdin);
            }
            break;
        }
    }
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    char buffer[8192];
    char replacement;
    size_t len;
    size_t buffer_size = sizeof(buffer);

    printf("Enter a string: ");
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Error reading input\n");
            clearerr(stdin);
        } else {
            fprintf(stderr, "Error: End of input reached\n");
        }
        return EXIT_FAILURE;
    }

    len = safe_strlen(buffer, buffer_size);

    if (len == 0 || buffer[0] == '\n') {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    if (len == buffer_size - 1 && buffer[len - 1] != '\n' && buffer[len - 1] != '\0') {
        fprintf(stderr, "Warning: Input may have been truncated\n");
        clear_input_buffer();
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Error: Empty string after newline removal\n");
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
        clear_input_buffer();
        return EXIT_FAILURE;
    }

    clear_input_buffer();

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return EXIT_FAILURE;
    }

    replace_spaces(buffer, replacement);
    printf("Modified string: %s\n", buffer);

    return EXIT_SUCCESS;
}