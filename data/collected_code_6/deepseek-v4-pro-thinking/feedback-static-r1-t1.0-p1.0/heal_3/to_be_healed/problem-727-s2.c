#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int remove_non_alnum(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return -1;
    }
    size_t read = 0, write = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < size && str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (isalnum((unsigned char)str[read])) {
            if (write < size - 1) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                str[write++] = str[read];
            } else {
                break;
            }
        }
        read++;
    }
    if (write < size) {
        str[write] = '\0';
    } else {
        str[size - 1] = '\0';
    }
    return 0;
}

int main(void) {
    char text[] = "Hello, World! 123";
    if (remove_non_alnum(text, sizeof(text)) != 0) {
        return EXIT_FAILURE;
    }
    printf("%s\n", text);
    return EXIT_SUCCESS;
}