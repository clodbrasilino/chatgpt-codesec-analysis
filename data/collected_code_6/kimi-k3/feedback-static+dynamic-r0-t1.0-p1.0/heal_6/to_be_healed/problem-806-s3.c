#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

int max_uppercase_run(const char *str) {
    int max_run = 0;
    int current_run = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }
    
    return max_run;
}

static bool read_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return false;
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        return false;
    }
    
    size_t len = strnlen(buffer, size);
    
    if (len == 0) {
        return false;
    }
    
    if (len < size && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    
    if (!read_line(buffer, sizeof(buffer))) {
        return 1;
    }
    
    int result = max_uppercase_run(buffer);
    printf("%d\n", result);
    
    return 0;
}