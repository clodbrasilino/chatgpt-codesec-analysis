#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace_spaces(char *str, char replacement) {
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
    return str;
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 256;
    size_t len;
    char replacement;
    char *result;

    input = malloc(bufsize);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(input, bufsize, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }

    len = strnlen(input, bufsize);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == bufsize - 1 && input[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        fprintf(stderr, "Error reading character\n");
        free(input);
        return 1;
    }

    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    result = replace_spaces(input, replacement);
    if (result == NULL) {
        fprintf(stderr, "Invalid input string\n");
        free(input);
        return 1;
    }

    printf("Modified string: %s\n", result);
    free(input);
    return 0;
}