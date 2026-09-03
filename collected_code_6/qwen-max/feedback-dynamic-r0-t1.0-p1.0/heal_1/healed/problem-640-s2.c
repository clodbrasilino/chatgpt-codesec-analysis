#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char *str) {
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    char *write_pos = result;
    int parenthesis_level = 0;

    for (const char *read_pos = str; *read_pos; read_pos++) {
        if (*read_pos == '(') {
            parenthesis_level++;
        } else if (*read_pos == ')') {
            parenthesis_level--;
        } else if (parenthesis_level == 0) {
            *write_pos++ = *read_pos;
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
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}