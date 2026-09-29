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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        if (contains_z(buffer)) {
            printf("Match found\n");
        } else {
            printf("No match\n");
        }
    }
    return 0;
}