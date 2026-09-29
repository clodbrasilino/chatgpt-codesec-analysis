#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_parentheses(char *str)
{
    if (str == NULL) {
        return;
    }
    char *read_ptr = str;
    char *write_ptr = str;
    int depth = 0;
    while (*read_ptr != '\0') {
        if (*read_ptr == '(') {
            depth++;
        } else if (*read_ptr == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int main(void)
{
    char *test_strings[] = {
        "Hello (World) Test",
        "No parentheses here",
        "(Remove)Keep(Remove)",
        "Nested (Outer (Inner) Outer) End",
        "Unmatched (Open",
        "Unmatched )Close(",
        "Multiple (One) Two (Three) Four"
    };
    size_t num_strings = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    for (i = 0; i < num_strings; i++) {
        if (test_strings[i] == NULL) {
            fprintf(stderr, "Null string encountered\n");
            return EXIT_FAILURE;
        }
        size_t len = strnlen(test_strings[i], 1024);
        char *buffer = (char *)malloc(len + 1);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        memcpy(buffer, test_strings[i], len);
        buffer[len] = '\0';
        printf("Original: %s\n", buffer);
        remove_parentheses(buffer);
        printf("Modified: %s\n\n", buffer);
        free(buffer);
    }
    return EXIT_SUCCESS;
}