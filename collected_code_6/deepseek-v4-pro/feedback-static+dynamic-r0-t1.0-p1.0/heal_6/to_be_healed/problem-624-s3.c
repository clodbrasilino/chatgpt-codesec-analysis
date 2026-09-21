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
    ssize_t nread;
    
    printf("Enter a string: ");
    fflush(stdout);
    
    errno = 0;
    nread = getline(&input, &len, stdin);
    
    if (nread == -1) {
        free(input);
        /* Possible weaknesses found:
         *  Same value in both branches of ternary operator. [duplicateValueTernary]
         */
        return (errno == ENOMEM) ? 1 : 1;
    }
    
    if (nread > 0) {
        size_t chars_read = (size_t)nread;
        if (chars_read <= len && input[chars_read - 1] == '\n') {
            input[chars_read - 1] = '\0';
        } else if (chars_read < len) {
            input[chars_read] = '\0';
        } else if (chars_read == len) {
            /* Possible weaknesses found:
             *  Common realloc mistake: 'input' nulled but not freed upon failure [memleakOnRealloc]
             */
            input = (char *)realloc(input, len + 1);
            if (input == NULL) {
                return 1;
            }
            input[len] = '\0';
        }
    }
    
    to_upper_case(input);
    
    printf("Uppercase: %s\n", input);
    
    free(input);
    return 0;
}