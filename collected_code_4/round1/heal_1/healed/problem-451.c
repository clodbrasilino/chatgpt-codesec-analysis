#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

char *remove_whitespace(char *input) {
    regex_t regex;
    regmatch_t match;
    char *plaintext = malloc(strlen(input) + 1);
    if (plaintext == NULL) {
        return NULL; /* failed to allocate memory */
    }

    if (0 != regcomp(&regex, "[^ \t\n]", REG_EXTENDED)) {
        free(plaintext);
        return NULL; /* failed to compile regex */
    }

    int i, j = 0;
    for (i = 0; input[i] != '\0'; ++i) {
        if (0 == regexec(&regex, input + i, 1, &match, 0)) {
            plaintext[j++] = input[i + match.rm_so];
        }
    }

    plaintext[j] = '\0';
    regfree(&regex);
    return plaintext;
}

int main(void) {
    char *input = "Hello, world!   ";
    char *plaintext = remove_whitespace(input);
    if (plaintext != NULL) {
        printf("%s", plaintext);
        free(plaintext);
    } else {
        printf("Failed to remove whitespace from string.\n");
    }
    return 0;
}