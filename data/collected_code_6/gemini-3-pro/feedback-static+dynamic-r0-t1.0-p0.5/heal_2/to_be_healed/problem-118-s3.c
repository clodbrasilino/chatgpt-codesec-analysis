#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[4096];
    
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }
    
    printf("[");
    int first = 1;
    char *p = line;
    
    while (*p) {
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }
        
        char *start = p;
        while (*p && !isspace((unsigned char)*p)) {
            p++;
        }
        
        if (!first) {
            printf(", ");
        }
        
        printf("'");
        for (char *c = start; c < p; c++) {
            putchar(*c);
        }
        printf("'");
        
        first = 0;
    }
    printf("]\n");
    
    return 0;
}