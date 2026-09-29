#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
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

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}