#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str, size_t len) {
    char *read = str;
    char *write = str;
    while (read - str < len && write - str < len - 1) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if ((*read - '0') % 2 == 0 || *read < '0' || *read > '9') {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
}

int main() {
    char str[] = "1234567890";
    remove_odd_chars(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}