#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 256

void remove_char(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    
    char *read_ptr = str;
    char *write_ptr = str;
    
    while (*read_ptr != '\0') {
        if (*read_ptr != ch) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char ch;
    int c;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strcspn(buffer, "\n");
    buffer[len] = '\0';
    
    if (scanf(" %c", &ch) != 1) {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == EOF) {
            break;
        }
    }
    
    if (c == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }
    
    remove_char(buffer, ch);
    
    printf("%s\n", buffer);
    
    return EXIT_SUCCESS;
}