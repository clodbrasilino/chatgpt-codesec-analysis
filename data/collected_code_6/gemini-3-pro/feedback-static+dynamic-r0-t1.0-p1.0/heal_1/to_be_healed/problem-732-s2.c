#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str) {
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
        }
        str++;
    }
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;

    read = getline(&input, &len, stdin);
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read != -1) {
        if (input[read - 1] == '\n') {
            input[read - 1] = '\0';
        }

        replace_chars(input);
        
        printf("%s\n", input);
    }

    free(input);
    input = NULL;

    return 0;
}