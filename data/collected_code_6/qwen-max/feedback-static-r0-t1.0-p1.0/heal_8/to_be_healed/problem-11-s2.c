#include <stdio.h>
#include <string.h>

void remove_char_occurrences(char *str, char c) {
    if (str == NULL) return;
    char *write = str;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (char *read = str; *read != '\0'; read++) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (*read != c) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write = *read;
            write++;
        }
    }
    *write = '\0';
}

int main() {
    char str[] = "programming";
    char c = 'm';
    remove_char_occurrences(str, c);
    printf("%s\n", str);
    return 0;
}