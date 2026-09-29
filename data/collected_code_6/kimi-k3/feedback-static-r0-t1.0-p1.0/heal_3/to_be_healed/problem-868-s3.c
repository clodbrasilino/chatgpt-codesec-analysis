#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    int len = 0;
    size_t i = max_len;

    if (i == 0) {
        return 0;
    }
    i--;

    while (i > 0 && s[i] == ' ') {
        i--;
    }

    while (i > 0 && s[i] != ' ') {
        len++;
        i--;
    }

    if (i == 0 && s[i] != ' ') {
        len++;
    }

    return len;
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;

    read = getline(&str, &size, stdin);
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read != -1) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read > 0 && str[read - 1] == '\n') {
            str[read - 1] = '\0';
            read--;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        printf("%d\n", lengthOfLastWord(str, (size_t)read));
        free(str);
    }

    return 0;
}