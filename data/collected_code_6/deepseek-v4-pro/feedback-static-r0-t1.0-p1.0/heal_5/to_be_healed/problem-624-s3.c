#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
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
    ssize_t nread;
    
    printf("Enter a string: ");
    errno = 0;
    nread = getline(&input, &len, stdin);
    
    if (nread == -1) {
        free(input);
        if (errno == ENOMEM) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        return 1;
    }
    
    if (nread > 0 && input[nread - 1] == '\n') {
        input[nread - 1] = '\0';
    } else if (nread == 0) {
        free(input);
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(input);
    if (str_len >= (size_t)nread) {
        free(input);
        fprintf(stderr, "String validation failed\n");
        return 1;
    }
    
    to_upper_case(input);
    
    printf("Uppercase: %s\n", input);
    
    free(input);
    
    return 0;
}