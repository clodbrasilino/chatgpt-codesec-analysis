#define _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_spaces(const char *str, size_t max_len) {
    if (str == NULL) return NULL;
    size_t len = strnlen(str, max_len);
    size_t spaces = 0;
    for (size_t i = 1; i < len; i++) {
        if (isupper((unsigned char)str[i]) && !isspace((unsigned char)str[i - 1])) {
            spaces++;
        }
    }
    size_t out_len = len + spaces;
    char *output = malloc(out_len + 1);
    if (output == NULL) return NULL;
    size_t j = 0;
    if (len > 0) output[j++] = str[0];
    for (size_t i = 1; i < len; i++) {
        if (isupper((unsigned char)str[i]) && !isspace((unsigned char)str[i - 1])) {
            output[j++] = ' ';
        }
        output[j++] = str[i];
    }
    output[j] = '\0';
    return output;
}

int main(void) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread = getline(&line, &bufsize, stdin);
    if (nread == -1) {
        free(line);
        return 1;
    }
    if (nread > 0 && line[nread - 1] == '\n') {
        line[nread - 1] = '\0';
        nread--;
    }
    char *result = insert_spaces(line, (size_t)nread);
    free(line);
    if (result == NULL) {
        fputs("Error processing string\n", stderr);
        return 1;
    }
    puts(result);
    free(result);
    return 0;
}