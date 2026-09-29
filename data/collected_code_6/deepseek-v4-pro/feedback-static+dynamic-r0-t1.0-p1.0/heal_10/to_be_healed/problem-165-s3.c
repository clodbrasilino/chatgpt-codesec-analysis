#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define MAX_INPUT_SIZE 4096

int count_same_position(const char *str) {
    size_t i;
    size_t len;
    int count;
    
    if (str == NULL) {
        return 0;
    }
    
    len = strnlen(str, MAX_INPUT_SIZE);
    count = 0;
    
    for (i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower = tolower((unsigned char)str[i]);
            if ((int)(lower - 'a') == (int)i) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char *buffer;
    size_t input_len;
    int result;
    
    buffer = calloc(MAX_INPUT_SIZE + 1, sizeof(char));
    if (buffer == NULL) {
        return 1;
    }
    
    printf("Enter a string: ");
    
    if (fgets(buffer, MAX_INPUT_SIZE + 1, stdin) == NULL) {
        if (ferror(stdin)) {
            clearerr(stdin);
        }
        free(buffer);
        return 1;
    }
    
    if (memchr(buffer, '\0', MAX_INPUT_SIZE + 1) == NULL) {
        buffer[MAX_INPUT_SIZE] = '\0';
    }
    
    input_len = strnlen(buffer, MAX_INPUT_SIZE + 1);
    if (input_len > 0 && buffer[input_len - 1] == '\n') {
        buffer[input_len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (ferror(stdin)) {
            clearerr(stdin);
        }
    }
    
    result = count_same_position(buffer);
    printf("%d\n", result);
    
    free(buffer);
    
    return 0;
}