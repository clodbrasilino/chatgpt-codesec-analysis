#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

void to_upper_case(char *str) {
    if (str == NULL) {
        return;
    }
    while (*str) {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;
    
    printf("Enter a string: ");
    errno = 0;
    read = getline(&input, &len, stdin);
    if (read == -1) {
        free(input);
        if (errno == ENOMEM) {
            return 1;
        }
        return 1;
    }
    
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        read--;
    } else if (read > 0 && (size_t)read < len) {
        input[read] = '\0';
    }
    
    to_upper_case(input);
    
    printf("Uppercase: %s\n", input);
    
    free(input);
    return 0;
}