#include <stdio.h>
#include <string.h>

void remove_char_occurrences(char *str, char c) {
    if (str == NULL) return;
    char *read = str;
    char *write = str;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read) {
        *write = *read++;
        write += (*write != c);
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