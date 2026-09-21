#include <stdio.h>
#include <string.h>

int has28Days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    if (strcmp(month, "February") == 0) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[64];
    
    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        size_t len = strnlen(month, sizeof(month));
        if (len > 0 && month[len - 1] == '\n') {
            month[len - 1] = '\0';
        } else if (len == sizeof(month) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        if (has28Days(month)) {
            printf("%s has 28 days.\n", month);
        } else {
            printf("%s does not have 28 days.\n", month);
        }
    }
    
    return 0;
}