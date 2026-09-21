#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int contains_z(const char *word) {
    if (word == NULL) {
        return 0;
    }
    while (*word != '\0') {
        if (*word == 'z') {
            return 1;
        }
        word++;
    }
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else if (len == sizeof(buffer) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        if (contains_z(buffer)) {
            printf("Match found\n");
        } else {
            printf("No match\n");
        }
    }
    return 0;
}