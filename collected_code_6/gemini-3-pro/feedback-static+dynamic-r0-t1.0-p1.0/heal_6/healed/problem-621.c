#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int main(void) {
    char *line = NULL;
    size_t size = 0;
    
    if (getline(&line, &size, stdin) == -1) {
        free(line);
        return 0;
    }

    char *comma = strrchr(line, ',');
    long k = 0;
    char *endptr;

    if (comma) {
        errno = 0;
        k = strtol(comma + 1, &endptr, 10);
        if (errno == ERANGE || k < INT_MIN || k > INT_MAX) {
            k = 0; 
        }
        *comma = '\0';
    } else {
        char *space = strrchr(line, ' ');
        if (space) {
            errno = 0;
            k = strtol(space + 1, &endptr, 10);
            if (errno == ERANGE || k < INT_MIN || k > INT_MAX) {
                k = 0;
            }
            *space = '\0';
        }
    }

    char *str = line;
    while (*str != '\0' && isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '"' || *str == '\'') {
        char quote = *str;
        str++;
        char *end = strrchr(str, quote);
        if (end) {
            *end = '\0';
        }
    }

    printf("[");
    int first = 1;
    char *p = str;
    
    while (*p) {
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        if (!*p) break;
        
        if (!first) {
            printf(", ");
        }
        first = 0;
        
        printf("'");
        while (*p && !isspace((unsigned char)*p)) {
            if (isdigit((unsigned char)*p)) {
                long val = 0;
                while (*p && isdigit((unsigned char)*p)) {
                    val = val * 10 + (*p - '0');
                    p++;
                }
                printf("%ld", val + k);
            } else {
                putchar(*p);
                p++;
            }
        }
        printf("'");
    }
    printf("]\n");

    free(line);
    return 0;
}