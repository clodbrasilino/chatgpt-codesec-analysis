#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

bool is_uppercase(char c) {
    return c >= 'A' && c <= 'Z';
}

char *add_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        char current = str[src_offset];

        if (is_uppercase(current)) {
            if (src_offset > 0 && str[src_offset - 1] != ' ') {
                result[dest_offset++] = ' ';
            }
            result[dest_offset++] = current;
            src_offset++;
        } else {
            result[dest_offset++] = current;
            src_offset++;
        }
    }

    if (dest_offset >= max_len) {
        free(result);
        return NULL;
    }

    result[dest_offset] = '\0';

    char *shrunk = realloc(result, dest_offset + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *result1 = add_spaces("HelloWorld");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = add_spaces("ThisIsATest");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = add_spaces("NoSpaces");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *result4 = add_spaces("already spaced");
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    char *result5 = add_spaces("");
    if (result5 != NULL) {
        printf("%s\n", result5);
        free(result5);
    }

    char *result6 = add_spaces(NULL);
    if (result6 != NULL) {
        printf("%s\n", result6);
        free(result6);
    } else {
        printf("NULL handled\n");
    }

    return 0;
}