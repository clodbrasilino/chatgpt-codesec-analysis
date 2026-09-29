#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("[]\n");
        return 0;
    }
    
    printf("[");
    char *token = strtok(buffer, " \t\r\n");
    int first = 1;
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