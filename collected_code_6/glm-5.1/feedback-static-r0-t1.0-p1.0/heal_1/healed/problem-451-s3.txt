#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    const char *p = str;
    while (*p) {
        if (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\r' && *p != '\f' && *p != '\v') {
            len++;
        }
        p++;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    p = str;
    while (*p) {
        if (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\r' && *p != '\f' && *p != '\v') {
            result[res_idx] = *p;
            res_idx++;
        }
        p++;
    }

    result[res_idx] = '\0';
    return result;
}

int main(void) {
    const char *input = " Hello \t World \n from C \r ";
    char *output = remove_whitespaces(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}