#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_spaces(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = ch;
        }
        i++;
    }
}

int main(void) {
    char *buffer = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;

    read = getline(&buffer, &len, stdin);
    if (read == -1) {
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    replace_spaces(buffer, '_');
    printf("%s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}