#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[4096];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }

    printf("[");
    int first = 1;
    char *token = strtok(line, " \t\r\n");
    
    while (token != NULL) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", token);
        first = 0;
        token = strtok(NULL, " \t\r\n");
    }
    
    printf("]\n");

    return 0;
}