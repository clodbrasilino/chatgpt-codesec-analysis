#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(input);
    char *output = (char *)malloc(len+1);
    if (!output) return NULL;
    int j = 0;
    int depth = 0;
    for (int i = 0; i < len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            depth--;
        } else if (depth == 0) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

int main() {
    const char *input = "Hello, (this is a test) and this should stay.";
    char *result = remove_parenthesis(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}