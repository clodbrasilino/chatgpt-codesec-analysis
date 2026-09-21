#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char *str) {
    size_t len = strnlen(str, 1024);
    if (len == 1024 && str[1023] != '\0') return NULL;
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    char *write_pos = result;
    int parenthesis_level = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            parenthesis_level++;
        } else if (str[i] == ')') {
            parenthesis_level--;
        } else if (parenthesis_level == 0) {
            *write_pos++ = str[i];
        }
    }

    *write_pos = '\0';
    return result;
}

int main() {
    const char input[] = "Example (with (nested) parenthesis) string.";
    char *output = remove_parenthesis(input);

    if (output) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}