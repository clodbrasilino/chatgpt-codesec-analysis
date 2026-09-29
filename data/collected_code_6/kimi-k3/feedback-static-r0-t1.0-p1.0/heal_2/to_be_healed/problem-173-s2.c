#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void remove_non_alphanumeric(char *str)
{
    size_t read_idx = 0;
    size_t write_idx = 0;
    
    if (str == NULL) {
        return;
    }
    
    while (str[read_idx] != '\0') {
        if (isalnum((unsigned char)str[read_idx])) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;
    int c;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    remove_non_alphanumeric(buffer);
    
    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}