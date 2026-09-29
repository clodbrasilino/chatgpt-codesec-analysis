#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool is_undulating(const char *num, size_t len) {
    if (len < 3) return false;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)num[i])) return false;
    }
    
    if (num[0] == num[1]) return false;
    
    for (size_t i = 1; i < len - 1; i++) {
        if (num[i] == num[i-1] || num[i] == num[i+1] || num[i-1] != num[i+1]) {
            return false;
        }
    }
    
    return num[len-1] != num[len-2];
}

int main(void) {
    enum { BUFFER_SIZE = 256 };
    char *input = NULL;
    size_t input_len = 0;
    size_t bufsize = 0;
    ssize_t nread;
    bool input_complete = false;
    
    printf("Enter a number: ");
    nread = getline(&input, &bufsize, stdin);
    if (nread == -1) {
        free(input);
        return 1;
    }
    
    input_len = (size_t)nread;
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
        input_complete = true;
    } else {
        enum { CHUNK_SIZE = 64 };
        char *discard = NULL;
        size_t discard_bufsize = 0;
        ssize_t discard_nread;
        bool newline_found = false;
        
        while (!newline_found) {
            discard_nread = getline(&discard, &discard_bufsize, stdin);
            if (discard_nread == -1) {
                break;
            }
            if (discard_nread > 0 && discard[discard_nread - 1] == '\n') {
                newline_found = true;
            }
        }
        
        free(discard);
        free(input);
        printf("Input too long\n");
        return 1;
    }
    
    if (!input_complete) {
        free(input);
        printf("Input too long\n");
        return 1;
    }
    
    if (input_len == 0) {
        free(input);
        printf("Empty input\n");
        return 1;
    }
    
    if (is_undulating(input, input_len)) {
        printf("%s is an undulating number\n", input);
    } else {
        printf("%s is not an undulating number\n", input);
    }
    
    free(input);
    return 0;
}