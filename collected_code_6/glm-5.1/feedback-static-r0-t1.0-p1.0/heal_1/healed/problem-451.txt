#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t write_pos = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r' && str[i] != '\v' && str[i] != '\f') {
            result[write_pos++] = str[i];
        }
    }

    result[write_pos] = '\0';

    char *shrunk = realloc(result, write_pos + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *result = remove_whitespaces("  H e l l o \t W o r l d \n ");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}