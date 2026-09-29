#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *line = NULL;
    size_t size = 0;
    
    if (getline(&line, &size, stdin) == -1) {
        free(line);
        return 0;
    }

    char *comma = strrchr(line, ',');
    int k = 0;
    if (comma) {
        k = atoi(comma + 1);
        *comma = '\0';
    } else {
        char *space = strrchr(line, ' ');
        if (space) {
            k = atoi(space + 1);
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