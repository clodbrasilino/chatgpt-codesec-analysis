#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int is_numeric(const char* s) {
    if (!s || !*s) return 0;
    if (*s == '-' && s[1]) s++;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

int parse_long(const char* str, long* val) {
    char* endptr;
    errno = 0;
    long res = strtol(str, &endptr, 10);
    if (errno != 0 || endptr == str || *endptr != '\0') {
        return 0;
    }
    *val = res;
    return 1;
}

int main(void) {
    char *input_line = NULL;
    size_t input_size = 0;
    char *k_line = NULL;
    size_t k_size = 0;
    
    if (getline(&input_line, &input_size, stdin) == -1) {
        free(input_line);
        return 0;
    }
    input_line[strcspn(input_line, "\r\n")] = '\0';
    
    long k = 0;
    int k_parsed = 0;
    
    if (getline(&k_line, &k_size, stdin) != -1) {
        k_line[strcspn(k_line, "\r\n")] = '\0';
        if (k_line[0] != '\0') {
            if (parse_long(k_line, &k)) {
                k_parsed = 1;
            }
        }
    }
    
    if (!k_parsed) {
        char *last_space = strrchr(input_line, ' ');
        if (last_space) {
            if (parse_long(last_space + 1, &k)) {
                *last_space = '\0';
            }
        }
    }

    printf("[");
    int first = 1;
    char* token = strtok(input_line, " ");
    while (token) {
        if (!first) printf(", ");
        if (is_numeric(token)) {
            char *endptr;
            errno = 0;
            long long val = strtoll(token, &endptr, 10);
            if (errno == 0 && *endptr == '\0') {
                printf("'%lld'", val + k);
            } else {
                printf("'%s'", token);
            }
        } else {
            printf("'%s'", token);
        }
        first = 0;
        token = strtok(NULL, " ");
    }
    printf("]\n");
    
    free(input_line);
    free(k_line);
    return 0;
}