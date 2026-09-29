#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

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

bool get_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return false;
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        return false;
    }
    
    size_t len = strnlen(buffer, size);
    
    if (len == size && buffer[size - 1] != '\0') {
        return false;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    return true;
}

bool get_character(char *ch) {
    if (ch == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int c = getchar();
    
    if (c == EOF) {
        return false;
    }
    
    while (c == ' ' || c == '\t') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (c == EOF) {
            return false;
        }
    }
    
    if (c == '\n') {
        return false;
    }
    
    *ch = (char)c;
    
    int next;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((next = getchar()) != '\n' && next != EOF) {
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char ch;
    
    if (!get_line(buffer, sizeof(buffer))) {
        return EXIT_FAILURE;
    }
    
    if (!get_character(&ch)) {
        return EXIT_FAILURE;
    }
    
    remove_char(buffer, ch);
    
    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}