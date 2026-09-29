#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace_spaces(char *str, size_t size, char replacement) {
    if (str == NULL) {
        return NULL;
    }

    size_t i = 0;
    while (i < size && str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
        i++;
    }
    return str;
}

int main(void) {
    char input[512];
    char replacement;
    char *result;
    size_t len;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (c == EOF) {
            clearerr(stdin);
        }
    }

    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        fprintf(stderr, "Error reading character\n");
        return 1;
    }

    result = replace_spaces(input, sizeof(input), replacement);
    if (result == NULL) {
        fprintf(stderr, "Invalid input string\n");
        return 1;
    }

    printf("Modified string: %s\n", result);
    return 0;
}