#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    bool has_a = false, has_e = false, has_i = false, has_o = false, has_u = false;
    
    for (const char *p = str; *p != '\0'; p++) {
        char c = tolower((unsigned char)*p);
        switch (c) {
            case 'a': has_a = true; break;
            case 'e': has_e = true; break;
            case 'i': has_i = true; break;
            case 'o': has_o = true; break;
            case 'u': has_u = true; break;
            default: break;
        }
        if (has_a && has_e && has_i && has_o && has_u) {
            return true;
        }
    }
    
    return false;
}

static void clear_input_line(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int safe_getline(char **line, size_t *size, FILE *stream) {
    if (line == NULL || size == NULL || stream == NULL) {
        return -1;
    }
    
    if (*line == NULL) {
        *size = BUFFER_SIZE;
        *line = malloc(*size);
        if (*line == NULL) {
            return -1;
        }
    }
    
    size_t pos = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    
    while (pos < *size - 1) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
        if (c == EOF) {
            if (pos == 0) {
                return -1;
            }
            break;
        }
        if (c == '\n') {
            (*line)[pos] = '\0';
            return pos;
        }
        (*line)[pos++] = (char)c;
    }
    
    (*line)[pos] = '\0';
    
    if (pos == *size - 1) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stream);
        if (next != '\n' && next != EOF) {
            clear_input_line();
            return -2;
        }
    }
    
    return pos;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    
    while ((bytes_read = safe_getline(&input, &buffer_size, stdin)) >= 0) {
        if (bytes_read >= BUFFER_SIZE) {
            fprintf(stderr, "Warning: Input truncated to %d characters\n", BUFFER_SIZE - 1);
        }
        
        if (contains_all_vowels(input)) {
            printf("Accepted: %s\n", input);
        } else {
            printf("Rejected: %s\n", input);
        }
    }
    
    free(input);
    
    if (ferror(stdin)) {
        clearerr(stdin);
        return 1;
    }
    
    return 0;
}