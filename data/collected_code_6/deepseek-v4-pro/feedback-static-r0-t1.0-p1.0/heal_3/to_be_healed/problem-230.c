#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        if (*str == ' ') {
            *str = replacement;
        }
        str++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    char replacement;
    size_t len;
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        return 1;
    }
    
    replace_spaces(str, replacement);
    
    printf("Modified string: %s\n", str);
    
    return 0;
}