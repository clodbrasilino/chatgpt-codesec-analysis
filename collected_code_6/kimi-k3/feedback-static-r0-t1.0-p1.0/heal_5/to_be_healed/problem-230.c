#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        return;
    }
    
    size_t i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char replacement;
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strcspn(buffer, "\n");
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
    } else {
        buffer[len] = '\0';
    }
    
    printf("Enter replacement character: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading replacement character\n");
        return EXIT_FAILURE;
    }
    
    if (c == '\n') {
        fprintf(stderr, "Invalid replacement character\n");
        return EXIT_FAILURE;
    }
    
    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    replacement = (char)c;
    
    replace_spaces(buffer, replacement);
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}